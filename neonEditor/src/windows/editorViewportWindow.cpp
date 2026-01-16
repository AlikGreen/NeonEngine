#include "editorViewportWindow.h"

#include <imgui.h>

#include "../editorCamera.h"
#include "core/engine.h"
#include "core/sceneManager.h"
#include "core/components/transformComponent.h"
#include "graphics/graphicsSystem.h"
#include "graphics/components/camera.h"
#include "graphics/components/pointLight.h"
#include "imgui/imGuiExtensions.h"
#include "input/input.h"

namespace Neon::Editor
{
    struct MatrixUniforms
    {
        glm::mat4 viewMatrix;
        glm::mat4 projMatrix;
        glm::mat4 modelMatrix;
    };


    void EditorViewportWindow::startup()
    {
        m_device = Engine::getSystem<GraphicsSystem>()->getDevice();

        AssetManager& assetManager = Engine::getAssetManager();
        const auto texData = assetManager.import<TextureData>("textures/light-bulb.png");
        const auto image = Image(texData);
        const auto viewDesc = RHI::TextureViewDescription(image.texture);
        m_lightTextureView = m_device->createTextureView(viewDesc);
        m_gizmoSampler = image.sampler;

        m_matrixUniformBuffer = m_device->createUniformBuffer();

        m_billboardMaterial = makeBox<MaterialShader>(MaterialShader::createBillboard());

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

        const auto cl = m_device->createCommandList();
        cl->begin();
        cl->reserveBuffer(m_matrixUniformBuffer, sizeof(MatrixUniforms));
        m_device->submit(cl);
    }

    void EditorViewportWindow::update()
    {
        auto& registry = Engine::getSceneManager().getCurrentScene().getRegistry();
        const auto cameras = registry.view<Camera, EditorCamera, Transform>();

        if(cameras.size() >= 1)
        {
            auto [camEntity, camera, editorCamera, camTransform] = cameras.at(0);

            if(Input::isButtonHeld(MouseButton::Right))
            {
                m_wasFocused = true;
                constexpr float sens = 5.0f; // In future get from settings
                float xDelta = Input::getMouseDelta().x * Engine::getDeltaTime() * sens;
                camTransform.rotate({ 0.0f, xDelta, 0.0f });
                float yDelta = Input::getMouseDelta().y * Engine::getDeltaTime() * sens;
                camTransform.rotate({ yDelta, 0.0f, 0.0f });

                constexpr float camSpeed = 5.0f; // In future get from settings

                if(Input::isKeyHeld(KeyCode::W))
                    camTransform.translate(camTransform.forward() * Engine::getDeltaTime() * camSpeed);
                if(Input::isKeyHeld(KeyCode::S))
                    camTransform.translate(camTransform.backward() * Engine::getDeltaTime() * camSpeed);
                if(Input::isKeyHeld(KeyCode::A))
                    camTransform.translate(camTransform.left() * Engine::getDeltaTime() * camSpeed);
                if(Input::isKeyHeld(KeyCode::D))
                    camTransform.translate(camTransform.right() * Engine::getDeltaTime() * camSpeed);
                if(Input::isKeyHeld(KeyCode::Space))
                    camTransform.translate(camTransform.up() * Engine::getDeltaTime() * camSpeed);
                if(Input::isKeyHeld(KeyCode::LShift))
                    camTransform.translate(camTransform.down() * Engine::getDeltaTime() * camSpeed);

                Input::setCursorLocked(true);
                Input::setCursorVisible(false);
            }else if(m_wasFocused)
            {
                m_wasFocused = false;

                Input::setCursorLocked(false);
                Input::setCursorVisible(true);
            }
        }
    }

    void EditorViewportWindow::render()
    {
        ImGui::Begin("Viewport");
        auto& registry = Engine::getSceneManager().getCurrentScene().getRegistry();
        const auto cameras = registry.view<Camera, EditorCamera, Transform>();

        const ImVec2 avail = ImGui::GetContentRegionAvail();

        if(cameras.size() >= 1)
        {
            auto [camEntity, camera, editorCamera, camTransform] = cameras.at(0);
            if(camera.renderTarget != nullptr)
            {
                camera.setAspectRatio(static_cast<float>(avail.x) / static_cast<float>(avail.y));
                renderBillboards(camEntity, camTransform, camera);
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

    void EditorViewportWindow::updateFramebuffer(const Rc<RenderTarget> &renderTarget)
    {
        const uint32_t width = renderTarget->getWidth();
        const uint32_t height = renderTarget->getHeight();

        if(m_framebuffer != nullptr && width == m_framebuffer->getWidth() && height == m_framebuffer->getHeight())
            return;

        const auto fbDesc = RHI::FramebufferDescription(renderTarget->getDepthAttachment(), renderTarget->getColorAttachment());
        m_framebuffer = m_device->createFramebuffer(fbDesc);
    }

    void EditorViewportWindow::renderBillboards(ECS::Entity camEntity, const Transform& camTransform, Camera& camera)
    {
        auto& registry = Engine::getSceneManager().getCurrentScene().getRegistry();

        const auto cl = m_device->createCommandList();

        updateFramebuffer(camera.renderTarget);

        cl->begin();
        cl->setPipeline(m_billboardMaterial->getPipeline());
        cl->setFramebuffer(m_framebuffer);

        const auto pointLights = registry.view<PointLight, Transform>();

        const glm::mat4 flip = glm::scale(glm::mat4(1.0f), glm::vec3(1, 1, -1));
        const glm::mat4 viewMatrix = glm::inverse(Transform::getWorldMatrix(camEntity) * flip);

        MatrixUniforms matrixUniforms{};
        matrixUniforms.projMatrix = camera.getProjectionMatrix();
        matrixUniforms.viewMatrix = viewMatrix;

        for(auto [entity, pointLight, transform] : pointLights)
        {
            matrixUniforms.modelMatrix = glm::inverse(glm::lookAt(transform.getPosition(), camTransform.getPosition(), transform.up()));
                // calculateBillboardMatrix(transform.getPosition(), matrixUniforms.viewMatrix, matrixUniforms.projMatrix);

            cl->updateBuffer(m_matrixUniformBuffer, matrixUniforms);
            cl->setUniformBuffer("MatrixUniforms", m_matrixUniformBuffer);
            cl->setSampler("gizmoSampler", m_gizmoSampler);
            cl->setTexture("gizmoTexture", m_lightTextureView);

            cl->setVertexBuffer(0, m_screenMesh.getVertexBuffer());
            cl->setIndexBuffer(m_screenMesh.getIndexBuffer(), RHI::IndexFormat::UInt32);

            cl->drawIndexed(6);
        }

        m_device->submit(cl);
    }
}
