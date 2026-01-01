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

        RHI::SamplerDescription samplerDesc{};
        samplerDesc.minFilter = RHI::TextureFilter::Linear;
        samplerDesc.magFilter = RHI::TextureFilter::Linear;
        samplerDesc.wrapMode.x = RHI::TextureWrap::ClampToEdge;
        samplerDesc.wrapMode.y = RHI::TextureWrap::ClampToEdge;
        samplerDesc.wrapMode.z = RHI::TextureWrap::ClampToEdge;

        // Use a temporary command list for initialization logic
        const Rc<RHI::CommandList> initCmdList = m_device->createCommandList();

        m_cameraUniformBuffer      = m_device->createUniformBuffer();
        m_modelUniformBuffer       = m_device->createUniformBuffer();
        m_pointLightsUniformBuffer = m_device->createUniformBuffer();

        m_screenMesh = Mesh();

        const std::vector screenVertices =
        {
            Vertex { {-1, -1, 0 }, { }, { 0, 0} },
            Vertex { { 1, -1, 0 }, { }, { 1, 0} },
            Vertex { { 1,  1, 0 }, { }, { 1, 1} },
            Vertex { {-1,  1, 0 }, { }, { 0, 1} },
        };

        const std::vector<uint32_t> quadIndices =
        {
            0, 1, 2,
            0, 2, 3
        };

        m_screenMesh.setVertices(screenVertices);
        m_screenMesh.setIndices(quadIndices);

        m_screenMesh.apply();


        DebugUniforms debugUniforms{};
        debugUniforms.debugUvs     = false;
        debugUniforms.debugNormals = false;

        initCmdList->begin();

        initCmdList->reserveBuffer(m_cameraUniformBuffer     , sizeof(CameraUniforms));
        initCmdList->reserveBuffer(m_modelUniformBuffer      , sizeof(MeshUniforms));
        initCmdList->reserveBuffer(m_pointLightsUniformBuffer, sizeof(PointLightUniforms));

        m_device->submit(initCmdList);
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

        const Rc<RHI::CommandList> cl = m_device->createCommandList();

        cl->begin();

        const Rc<RHI::Framebuffer> framebuffer = camera.getFramebuffer();
        cl->setFramebuffer(framebuffer);

        cl->clearColorTarget(0, {camera.bgColor.x, camera.bgColor.y, camera.bgColor.z, 1.0f});
        cl->clearDepthStencil(1.0f);

        const glm::mat4 flip = glm::scale(glm::mat4(1.0f), glm::vec3(1, 1, -1));
        const glm::mat4 viewMatrix = glm::inverse(Transform::getWorldMatrix(camEntity) * flip);

        CameraUniforms cameraMatrices = {
            viewMatrix,
            camera.getProjectionMatrix(),
        };

        cl->updateBuffer(m_cameraUniformBuffer, cameraMatrices);

        const AssetRef<MaterialShader> material = camera.getSkyboxMaterial();

        if(material)
        {
            const Rc<RHI::Pipeline> matPipeline = material->getPipeline();
            if(matPipeline != m_currentScenePipeline)
            {
                m_currentScenePipeline = matPipeline;
                cl->setPipeline(m_currentScenePipeline);
            }

            cl->setUniformBuffer("CameraUniforms", m_cameraUniformBuffer);

            material->bindUniforms(cl);

            cl->setVertexBuffer(0, m_screenMesh.getVertexBuffer());
            cl->setIndexBuffer(m_screenMesh.getIndexBuffer(), RHI::IndexFormat::UInt32);
            cl->drawIndexed(6);
        }

        // --- 4. Render Scene ---

        const auto& pointLights = registry.view<PointLight, Transform>();
        PointLightUniforms pointLightUniforms{};
        int lightIndex = 0;

        for (auto[entity, pointLight, transform] : pointLights)
        {
            pointLightUniforms.pointLights[lightIndex] = {
                transform.getPosition(),
                pointLight.power,
                pointLight.color,
            };

            lightIndex++;
            if(lightIndex >= 32) break;
        }
        pointLightUniforms.pointLightsCount = lightIndex;

        cl->updateBuffer(m_pointLightsUniformBuffer, pointLightUniforms);

        // Cull and Sort Meshes
        const auto& meshRenderers = registry.view<MeshRenderer, Transform>();
        std::vector<std::pair<ECS::Entity, MeshRenderer&>> orderedAndCulledEntities;
        orderedAndCulledEntities.reserve(meshRenderers.size());

        for (auto[entity, meshRenderer, transform] : meshRenderers)
        {
            if(meshRenderer.mesh == nullptr) continue;

            glm::mat4 worldMat = Transform::getWorldMatrix(entity);
            if(camera.getFrustum(glm::inverse(worldMat)).intersects(meshRenderer.mesh->getBounds()))
            {
                orderedAndCulledEntities.emplace_back(entity, meshRenderer);
            }
        }

        for (const auto& [entity, meshRenderer]: orderedAndCulledEntities)
        {
            renderMesh(cl, entity, meshRenderer);
        }

        m_device->submit(cl);
    }

    void RenderSystem::renderMesh(const Rc<RHI::CommandList>& cl, const ECS::Entity entity, const MeshRenderer& meshRenderer)
    {
        const glm::mat4 modelMatrix = Transform::getWorldMatrix(entity);

        MeshUniforms modelUniforms = { modelMatrix };

        cl->updateBuffer(m_modelUniformBuffer, modelUniforms);

        for(int i = 0; i < meshRenderer.materials.size(); i++)
        {
            renderSubMesh(cl, meshRenderer, i);
        }
    }

    void RenderSystem::renderSubMesh(const Rc<RHI::CommandList>& cl, const MeshRenderer& meshRenderer, const int materialIndex)
    {
        if(meshRenderer.materials.size() <= materialIndex ||
           meshRenderer.mesh->getPrimitives().size() <= materialIndex) return;

        const AssetRef<MaterialShader> material = meshRenderer.materials[materialIndex];

        const Rc<RHI::Pipeline> matPipeline = material->getPipeline();
        if(matPipeline != m_currentScenePipeline)
        {
            m_currentScenePipeline = matPipeline;
            cl->setPipeline(m_currentScenePipeline);
        }


        cl->setUniformBuffer("CameraUniforms", m_cameraUniformBuffer);
        cl->setUniformBuffer("PointLightUniforms", m_pointLightsUniformBuffer);
        cl->setUniformBuffer("ModelUniforms", m_modelUniformBuffer);

        material->bindUniforms(cl);

        const Primitive primitive = meshRenderer.mesh->getPrimitives().at(materialIndex);

        cl->setVertexBuffer(0, meshRenderer.mesh->getVertexBuffer());
        cl->setIndexBuffer(meshRenderer.mesh->getIndexBuffer(), RHI::IndexFormat::UInt32);
        cl->drawIndexed(primitive.indexCount, 1, primitive.indexStart);
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

    Rc<RHI::TextureView> RenderSystem::getOrCreateTextureView(const AssetRef<Rc<RHI::Texture>>& texture) const
    {
        const RHI::TextureViewDescription viewDesc{ *texture };
        return getOrCreateTextureView(texture, viewDesc);
    }

    Rc<RHI::TextureView> RenderSystem::getOrCreateTextureView(const AssetRef<Rc<RHI::Texture>>& texture, const RHI::TextureViewDescription& viewDesc) const
    {
        if(texture == nullptr) return nullptr;

        if(m_textureViewCache.contains(texture.getID()))
            return m_textureViewCache.at(texture.getID());

        Rc<RHI::TextureView> view = m_device->createTextureView(viewDesc);
        m_textureViewCache.emplace(texture.getID(), view);

        return view;
    }
}