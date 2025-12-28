#include "renderSystem.h"

#include <tiny_gltf.h>
#include <neonRHI/neonRHI.h>

#include "graphicsSystem.h"
#include "materialShader.h"
#include "mesh.h"
#include "asset/assetManager.h"
#include "components/camera.h"
#include "components/pointLight.h"
#include "core/engine.h"
#include "core/eventManager.h"
#include "core/sceneManager.h"
#include "core/components/transformComponent.h"
#include "enums/imageAccess.h"
#include "events/windowResizeEvent.h"
#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtx/dual_quaternion.hpp"

namespace Neon
{
    void RenderSystem::preStartup()
    {
        m_graphicsSystem = Engine::getSystem<GraphicsSystem>();

        m_window = m_graphicsSystem->getWindow();
        m_device = m_graphicsSystem->getDevice();

        // Create the persistent command list for the render loop
        m_commandList = m_device->createCommandList();

        RHI::SamplerDescription samplerDesc{};
        samplerDesc.minFilter = RHI::TextureFilter::Linear;
        samplerDesc.magFilter = RHI::TextureFilter::Linear;
        samplerDesc.wrapMode.x = RHI::TextureWrap::ClampToEdge;
        samplerDesc.wrapMode.y = RHI::TextureWrap::ClampToEdge;
        samplerDesc.wrapMode.z = RHI::TextureWrap::ClampToEdge;

        m_skyboxSampler = m_device->createSampler(samplerDesc);

        createSkyboxRenderPipeline();
        createEquirectToCubeMapPipeline();

        // Use a temporary command list for initialization logic
        const Rc<RHI::CommandList> initCmdList = m_device->createCommandList();

        m_cameraUniformBuffer      = m_device->createUniformBuffer();
        m_modelUniformBuffer       = m_device->createUniformBuffer();
        m_pointLightsUniformBuffer = m_device->createUniformBuffer();
        m_equirectParamsBuffer     = m_device->createUniformBuffer();

        m_screenQuadVertexBuffer = m_device->createVertexBuffer();
        m_screenQuadIndexBuffer  = m_device->createIndexBuffer();

        const std::vector<glm::vec2> quadPositions =
        {
            {-1, -1 },
            { 1, -1 },
            { 1,  1 },
            {-1,  1 }
        };

        const std::vector<uint32_t> quadIndices =
        {
            0, 1, 2,
            0, 2, 3
        };

        DebugUniforms debugUniforms{};
        debugUniforms.debugUvs     = false;
        debugUniforms.debugNormals = false;

        initCmdList->begin();

        initCmdList->reserveBuffer(m_cameraUniformBuffer     , sizeof(CameraUniforms));
        initCmdList->reserveBuffer(m_modelUniformBuffer      , sizeof(MeshUniforms));
        initCmdList->reserveBuffer(m_pointLightsUniformBuffer, sizeof(PointLightUniforms));
        initCmdList->reserveBuffer(m_equirectParamsBuffer    , sizeof(EquirectParamsUniforms));

        initCmdList->reserveBuffer(m_screenQuadVertexBuffer, quadPositions.size() * sizeof(glm::vec2));
        initCmdList->updateBuffer(m_screenQuadVertexBuffer, quadPositions);

        initCmdList->reserveBuffer(m_screenQuadIndexBuffer, quadIndices.size() * sizeof(uint32_t));
        initCmdList->updateBuffer(m_screenQuadIndexBuffer, quadIndices);

        m_device->submit(initCmdList);

        AssetHandle skyboxAssetHandle = Engine::getAssetManager().loadAsset<Image>("textures/skybox.hdr");
        m_skybox = Engine::getAssetManager().getAsset<Image>(skyboxAssetHandle).texture;
    }

    void RenderSystem::postStartup()
    {
        auto& world = Engine::getSceneManager().getCurrentScene().getRegistry();
        const auto cameras = world.view<Camera>();

        for(auto [entity, camera] : cameras)
        {
            if(camera.matchWindowSize)
            {
                camera.setWidth(m_window->getWidth());
                camera.setHeight(m_window->getHeight());
            }
        }
    }

    void RenderSystem::render()
    {
        auto& registry = Engine::getSceneManager().getCurrentScene().getRegistry();
        const auto cameras = registry.view<Camera, Transform>();

        if(cameras.size() < 1) return;

        auto [camEntity, camera, camTransform] = cameras.at(0);

        m_commandList->begin();

        const Rc<RHI::Framebuffer> framebuffer = camera.getFramebuffer();
        m_commandList->setFramebuffer(framebuffer);

        m_commandList->clearColorTarget(0, {0.0f, 1.0f, 0.0f, 1.0f});
        m_commandList->clearDepthStencil(1.0f);

        const glm::mat4 flip = glm::scale(glm::mat4(1.0f), glm::vec3(1, 1, -1));
        const glm::mat4 viewMatrix = glm::inverse(Transform::getWorldMatrix(camEntity) * flip);

        CameraUniforms cameraMatrices = {
            viewMatrix,
            camera.getProjectionMatrix(),
        };

        m_commandList->updateBuffer(m_cameraUniformBuffer, cameraMatrices);

        m_currentScenePipeline = m_skyboxPipeline;
        m_commandList->setPipeline(m_currentScenePipeline);

        const AssetRef<Rc<RHI::Texture>> cubeMap = getOrCreateCubeMap(m_skybox);
        const Rc<RHI::TextureView> cubeMapTextureView = getOrCreateTextureView(cubeMap);

        m_commandList->setSampler("skyboxTexture", m_skyboxSampler);
        m_commandList->setTexture("skyboxTexture", cubeMapTextureView);
        m_commandList->setUniformBuffer("CameraUniforms", m_cameraUniformBuffer);

        m_commandList->setVertexBuffer(0, m_screenQuadVertexBuffer);
        m_commandList->setIndexBuffer(m_screenQuadIndexBuffer, RHI::IndexFormat::UInt32);
        m_commandList->drawIndexed(6);

        // --- 4. Render Scene ---

        // const auto& pointLights = registry.view<PointLight, Transform>();
        // PointLightUniforms pointLightUniforms{};
        // int lightIndex = 0;
        //
        // for (auto[entity, pointLight, transform] : pointLights)
        // {
        //     pointLightUniforms.pointLights[lightIndex] = {
        //         transform.getPosition(),
        //         pointLight.power,
        //         pointLight.color,
        //     };
        //
        //     lightIndex++;
        //     if(lightIndex >= 32) break;
        // }
        // pointLightUniforms.pointLightsCount = lightIndex;
        //
        // m_commandList->updateBuffer(m_pointLightsUniformBuffer, pointLightUniforms);
        //
        // // Cull and Sort Meshes
        // const auto& meshRenderers = registry.view<MeshRenderer, Transform>();
        // std::vector<std::pair<ECS::Entity, MeshRenderer&>> orderedAndCulledEntities;
        // orderedAndCulledEntities.reserve(meshRenderers.size());
        //
        // for (auto[entity, meshRenderer, transform] : meshRenderers)
        // {
        //     if(meshRenderer.mesh == nullptr) continue;
        //
        //     glm::mat4 worldMat = Transform::getWorldMatrix(entity);
        //     if(camera.getFrustum(glm::inverse(worldMat)).intersects(meshRenderer.mesh->getBounds()))
        //     {
        //         orderedAndCulledEntities.emplace_back(entity, meshRenderer);
        //     }
        // }
        //
        // // Draw Meshes
        // for (const auto& [entity, meshRenderer]: orderedAndCulledEntities)
        // {
        //     renderMesh(entity, meshRenderer);
        // }

        // --- 5. Submit ---
        m_device->submit(m_commandList);
    }

    void RenderSystem::renderMesh(const ECS::Entity entity, const MeshRenderer& meshRenderer)
    {
        const glm::mat4 modelMatrix = Transform::getWorldMatrix(entity);

        MeshUniforms modelUniforms = { modelMatrix };

        m_commandList->updateBuffer(m_modelUniformBuffer, modelUniforms);

        for(int i = 0; i < meshRenderer.materials.size(); i++)
        {
            renderSubMesh(meshRenderer, i);
        }
    }

    void RenderSystem::renderSubMesh(const MeshRenderer& meshRenderer, const int materialIndex)
    {
        if(meshRenderer.materials.size() <= materialIndex ||
           meshRenderer.mesh->getPrimitives().size() <= materialIndex) return;

        const AssetRef<MaterialShader> material = meshRenderer.materials[materialIndex];

        const Rc<RHI::Pipeline> matPipeline = material->getPipeline();
        if(matPipeline != m_currentScenePipeline)
        {
            m_currentScenePipeline = matPipeline;
            m_commandList->setPipeline(m_currentScenePipeline);
        }


        m_commandList->setUniformBuffer("CameraUniforms", m_cameraUniformBuffer);
        m_commandList->setUniformBuffer("PointLightUniforms", m_pointLightsUniformBuffer);
        m_commandList->setUniformBuffer("ModelUniforms", m_modelUniformBuffer);

        material->bindUniforms(m_commandList);

        const Primitive primitive = meshRenderer.mesh->getPrimitives().at(materialIndex);

        m_commandList->setVertexBuffer(0, meshRenderer.mesh->getVertexBuffer());
        m_commandList->setIndexBuffer(meshRenderer.mesh->getIndexBuffer(), RHI::IndexFormat::UInt32);
        m_commandList->drawIndexed(primitive.indexCount, 1, primitive.indexStart);
    }

    void RenderSystem::event(Event *event)
    {
        if(const auto resize = dynamic_cast<WindowResizeEvent*>(event))
        {
            auto& world = Engine::getSceneManager().getCurrentScene().getRegistry();
            const auto cameras = world.view<Camera>();

            for(auto [entity, camera] : cameras)
            {
                if(camera.matchWindowSize)
                {
                    camera.setWidth(resize->width);
                    camera.setHeight(resize->height);
                }
            }
        }
    }

    void RenderSystem::createSkyboxRenderPipeline()
    {
        AssetManager& assetManager = Engine::getAssetManager();
        const auto shaderHandle = assetManager.loadAsset<Rc<RHI::Shader>>("shaders/skybox.glsl");
        const auto& shader = assetManager.getAsset<Rc<RHI::Shader>>(shaderHandle);
        shader->compile();

        RHI::InputLayout vertexInputState{};
        vertexInputState.addVertexBuffer<glm::vec2>(0);
        vertexInputState.addVertexAttribute<glm::vec2>(0, 0);

        RHI::DepthState depthState{};
        depthState.hasDepthTarget  = false; // Skybox usually drawn first with no depth or last at max depth
        depthState.enableDepthTest = false;

        RHI::RasterizerState rasterizerState{};
        rasterizerState.cullMode = RHI::CullMode::None;

        const RHI::RenderTargetsDescription targetsDesc{};

        RHI::BlendState blendState{};
        blendState.enableBlend = false;

        RHI::GraphicsPipelineDescription pipelineDescription{};
        pipelineDescription.shader             = shader;
        pipelineDescription.inputLayout        = vertexInputState;
        pipelineDescription.targetsDescription = targetsDesc;
        pipelineDescription.depthState         = depthState;
        pipelineDescription.rasterizerState    = rasterizerState;
        pipelineDescription.blendState         = blendState;

        m_skyboxPipeline = m_device->createPipeline(pipelineDescription);
    }

    void RenderSystem::createEquirectToCubeMapPipeline()
    {
        AssetManager& assetManager = Engine::getAssetManager();
        const auto shaderHandle = assetManager.loadAsset<Rc<RHI::Shader>>("shaders/equirectToCubeMap.glsl");
        const auto& shader = assetManager.getAsset<Rc<RHI::Shader>>(shaderHandle);
        shader->compile();

        RHI::ComputePipelineDescription pipelineDescription{};
        pipelineDescription.shader          = shader;
        pipelineDescription.threadGroupSize = { 16, 16, 1 };

        m_equirectToCubeMapPipeline = m_device->createPipeline(pipelineDescription);
    }

    AssetRef<Rc<RHI::Texture>> RenderSystem::getOrCreateCubeMap(const AssetRef<Rc<RHI::Texture>> equirectTexture) const
    {
        if(m_cubeMapCache.contains(equirectTexture.getHandle()))
            return m_cubeMapCache.at(equirectTexture.getHandle());

        constexpr uint32_t textureSize = 1024;

        const RHI::TextureDescription equirectTextureDesc = RHI::TextureDescription::TextureCube(
            textureSize,
            RHI::PixelFormat::R32G32B32A32Float,
            RHI::TextureUsage::Sampled | RHI::TextureUsage::ComputeStorageWrite);

        const Rc<RHI::Texture> cubeMap = m_device->createTexture(equirectTextureDesc);

        uint32_t groupsX = (textureSize + 15) / 16;
        uint32_t groupsY = (textureSize + 15) / 16;

        // Use a temporary command list for this one-time operation
        const Rc<RHI::CommandList> commandList = m_device->createCommandList();

        const RHI::TextureViewDescription viewDesc{ cubeMap };
        const Rc<RHI::TextureView> cubeMapTextureView = m_device->createTextureView(viewDesc);
        const Rc<RHI::TextureView> equirectTextureView = getOrCreateTextureView(equirectTexture);

        commandList->begin();
        commandList->setPipeline(m_equirectToCubeMapPipeline);

        for(int i = 0; i < 6; i++)
        {
            EquirectParamsUniforms uniforms{};
            uniforms.faceIndex = i;
            uniforms.outSize = textureSize;

            commandList->updateBuffer(m_equirectParamsBuffer, uniforms);
            commandList->setUniformBuffer("Params", m_equirectParamsBuffer);
            commandList->setTexture("uEquirect", equirectTextureView);
            commandList->setImage("uOutCube", cubeMapTextureView, RHI::ImageAccess::WriteOnly);
            commandList->dispatch({groupsX, groupsY, 1});
        }

        commandList->resourceBarrier(cubeMap);

        m_device->submit(commandList);

        AssetRef<Rc<RHI::Texture>> texture = Engine::getAssetManager().addAsset(cubeMap, "Cube map texture");
        m_cubeMapCache.emplace(equirectTexture.getHandle(), texture);

        return texture;
    }

    Rc<RHI::TextureView> RenderSystem::getOrCreateTextureView(const AssetRef<Rc<RHI::Texture>>& texture) const
    {
        const RHI::TextureViewDescription viewDesc{ *texture };
        return getOrCreateTextureView(texture, viewDesc);
    }

    Rc<RHI::TextureView> RenderSystem::getOrCreateTextureView(const AssetRef<Rc<RHI::Texture>>& texture, const RHI::TextureViewDescription& viewDesc) const
    {
        if(texture == nullptr) return nullptr;

        if(m_textureViewCache.contains(texture.getHandle()))
            return m_textureViewCache.at(texture.getHandle());

        Rc<RHI::TextureView> view = m_device->createTextureView(viewDesc);
        m_textureViewCache.emplace(texture.getHandle(), view);

        return view;
    }
}