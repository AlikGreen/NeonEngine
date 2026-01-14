#include "gameWindow.h"

#include <imgui.h>

#include "core/engine.h"
#include "core/sceneManager.h"
#include "core/components/transformComponent.h"
#include "graphics/graphicsSystem.h"
#include "graphics/components/camera.h"
#include "graphics/components/pointLight.h"
#include "imgui/imGuiExtensions.h"

namespace Neon::Editor
{
    struct Uniforms
    {
        glm::mat4 viewMatrix;
        glm::mat4 projMatrix;
        int windowWidth;
        int windowHeight;
        int gizmoCount = 0;
        alignas(16) glm::vec4 gizmoPositions[64]{};
    };

    void GameWindow::init()
    {
        m_device = Engine::getSystem<GraphicsSystem>()->getDevice();

        AssetManager& assetManager = Engine::getAssetManager();
        const auto shader = assetManager.import<Rc<RHI::Shader>>("shaders/billboard.slang");

        const auto texData = assetManager.import<TextureData>("textures/light-bulb.png");
        auto image = Image(texData);
        const auto viewDesc = RHI::TextureViewDescription(image.texture);
        m_lightTextureView = m_device->createTextureView(viewDesc);
        m_gizmoSampler = image.sampler;

        RHI::ComputePipelineDescription pipelineDescription{};
        pipelineDescription.shader             = shader.get();
        pipelineDescription.threadGroupSize    = {16, 16, 1};

        m_pipeline = m_device->createPipeline(pipelineDescription);

        m_uniformBuffer = m_device->createUniformBuffer();

        const auto cl = m_device->createCommandList();
        cl->begin();
        cl->reserveBuffer(m_uniformBuffer, sizeof(Uniforms));
        m_device->submit(cl);
    }

    void GameWindow::render()
    {
        ImGui::Begin("Game");
        auto& world = Engine::getSceneManager().getCurrentScene().getRegistry();
        const auto cameras = world.view<Camera, Transform>();

        const ImVec2 avail = ImGui::GetContentRegionAvail();

        if(cameras.size() >= 1)
        {
            auto [camEntity, camera, camTransform] = cameras.at(0);
            if(camera.renderTarget != nullptr)
            {
                camera.setAspectRatio(static_cast<float>(avail.x) / static_cast<float>(avail.y));
                renderBillboards(camTransform, camera);
                const Rc<RHI::TextureView> sceneTexture = camera.renderTarget->getColorAttachment();
                NeonGui::Image(sceneTexture, avail, ImVec2(0, 1), ImVec2(1, 0));
                camera.renderTarget->resize(static_cast<uint32_t>(avail.x), static_cast<uint32_t>(avail.y));

                if (ImGui::BeginDragDropTarget())
                {
                    if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("ASSET_ID"))
                    {
                        AssetManager& assetManager = Engine::getAssetManager();
                        Scene& currentScene = Engine::getSceneManager().getCurrentScene();
                        const AssetID droppedID = *static_cast<AssetID*>(payload->Data);

                        if(assetManager.assetIsType<Scene>(droppedID))
                        {
                            const AssetRef<Scene> prefab = assetManager.getAsset<Scene>(droppedID);
                            currentScene.import(prefab.get());
                        }
                    }
                    ImGui::EndDragDropTarget();
                }
            }
        }
        ImGui::End();

    }

    void GameWindow::renderBillboards(const Transform& camTransform, Camera& camera)
    {
        auto& registry = Engine::getSceneManager().getCurrentScene().getRegistry();

        const auto cl = m_device->createCommandList();

        cl->begin();
        cl->setPipeline(m_pipeline);

        Uniforms uniforms{};

        const auto pointLights = registry.view<PointLight, Transform>();

        int index = 0;

        uniforms.projMatrix = camera.getProjectionMatrix();
        uniforms.viewMatrix = inverse(camTransform.getLocalMatrix());

        const Rc<RHI::TextureView> colorTexture = camera.renderTarget->getColorAttachment();

        const int width = static_cast<int>(colorTexture->getWidth());
        const int height = static_cast<int>(colorTexture->getHeight());

        uniforms.windowWidth = width;
        uniforms.windowHeight = height;

        for(auto [entity, pointLight, transform] : pointLights)
        {
            glm::vec3 pos = transform.getPosition();
            constexpr float radius   = 5.0f;
            uniforms.gizmoPositions[index] = glm::vec4(pos, radius);
            index++;
            uniforms.gizmoCount = index;
            if(index >= 64) break;
        }

        cl->updateBuffer(m_uniformBuffer, uniforms);
        cl->setUniformBuffer("Uniforms", m_uniformBuffer);
        cl->setImage("sceneColorTexture", colorTexture, RHI::ImageAccess::ReadWrite);
        cl->setSampler("gizmoSampler", m_gizmoSampler);
        cl->setTexture("gizmoTexture", m_lightTextureView);

        cl->dispatch({ (width + 15) / 16, (height + 15) / 16, 1  });

        m_device->submit(cl);
    }
}
