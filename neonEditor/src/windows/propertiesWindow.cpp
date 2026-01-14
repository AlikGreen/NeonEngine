#include "propertiesWindow.h"

#include "sceneGraphWindow.h"
#include "../editorSystem.h"
#include "core/engine.h"
#include "core/components/tagComponent.h"
#include "core/components/transformComponent.h"
#include "graphics/imGuiSystem.h"
#include "graphics/components/camera.h"
#include "graphics/components/pointLight.h"
#include "imgui/imGuiExtensions.h"
#include "../util/propertyGrid.h"

namespace Neon::Editor
{
    void PropertiesWindow::render()
    {
        ImGui::Begin("Properties");
        if(m_latestViewedType == LastSelected::Entity && m_latestEntity.has_value())
            drawEntity(m_latestEntity.value());

        if(m_latestViewedType == LastSelected::Asset && m_latestAsset.has_value())
            drawAsset(m_latestAsset.value());

        ImGui::End();
    }

    void PropertiesWindow::view(ECS::Entity entity)
    {
        m_latestViewedType = LastSelected::Entity;
        m_latestEntity = entity;
    }

    void PropertiesWindow::view(const AssetID asset)
    {
        m_latestViewedType = LastSelected::Asset;
        m_latestAsset = asset;
    }

    void PropertiesWindow::stopViewing()
    {
        m_latestViewedType = LastSelected::None;
        m_latestAsset = std::nullopt;
        m_latestEntity = std::nullopt;
    }

    void PropertiesWindow::drawEntity(ECS::Entity entity)
    {
        ImGui::Spacing();
        if (entity.has<Tag>())
        {
            drawComponentSpacing();
            drawComponent<Tag>(entity);
        }
        if (entity.has<Transform>())
        {
            drawComponentSpacing();
            drawComponent<Transform>(entity);
        }
        if (entity.has<Camera>())
        {
            drawComponentSpacing();
            drawComponent<Camera>(entity);
        }
        if (entity.has<PointLight>())
        {
            drawComponentSpacing();
            drawComponent<PointLight>(entity);
        }
        if (entity.has<MeshRenderer>())
        {
            drawComponentSpacing();
            drawComponent<MeshRenderer>(entity);
        }

        drawComponentSpacing();

        const float width = ImGui::GetContentRegionAvail().x;
        if (ImGui::Button("Add Component", ImVec2(width, 0)))
        {
            ImGui::OpenPopup("componentPopup");
        }

        auto* editorSystem = Engine::getSystem<EditorSystem>();

        if (ImGui::BeginPopup("componentPopup"))
        {
            for(const auto& component : editorSystem->getComponents())
            {
                if(ImGui::Button(component.name.c_str()))
                {
                    component.emplaceCallback(entity);
                    ImGui::CloseCurrentPopup();
                }
            }

            ImGui::EndPopup();
        }
    }

    void PropertiesWindow::drawAsset(const AssetID asset)
    {
        AssetManager& assetManager = Engine::getAssetManager();
        ImGui::PushFont(ImGuiSystem::headingFont);
        const AssetMetadata metadata = assetManager.getMetadata(asset);
        ImGui::TextUnformatted(metadata.name.c_str());
        ImGui::PopFont();

        if(metadata.type == typeid(Mesh))
            drawAssetType<Mesh>(asset);
    }

    void PropertiesWindow::drawComponentSpacing()
    {
        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();
    }

    void PropertiesWindow::drawComponentTitle(const char* text)
    {
        ImGui::PushFont(ImGuiSystem::headingFont);

        ImDrawList* drawList = ImGui::GetWindowDrawList();
        const ImGuiStyle& style = ImGui::GetStyle();

        const ImVec2 startPos = ImGui::GetCursorScreenPos();
        const float width = ImGui::GetContentRegionAvail().x;

        const float paddingX = style.FramePadding.x;
        const float paddingY = style.FramePadding.y;

        const float textHeight = ImGui::GetTextLineHeight();
        const float height = textHeight + paddingY * 2.0f;

        const ImVec2 min = startPos;
        const auto max = ImVec2(startPos.x + width, startPos.y + height);

        drawList->AddRectFilled(min, max, 0x22ffffff, style.FrameRounding);

        ImGui::SetCursorScreenPos(ImVec2(startPos.x + paddingX, startPos.y + paddingY));
        ImGui::TextUnformatted(text);

        ImGui::SetCursorScreenPos(ImVec2(startPos.x, max.y));
        ImGui::PopFont();
        ImGui::Dummy({0.0f, 8.0f});
    }

    template<>
    void PropertiesWindow::drawComponent<Transform>(ECS::Entity entity)
    {
        auto& transform = entity.get<Transform>();

        drawComponentTitle("Transform");

        PropertyGrid grid("##TransformGrid");
        if (!grid.isOpen())
        {
            return;
        }

        glm::vec3 position = transform.getPosition();
        grid.nextRow("Position");
        if (ImGui::DragFloat3("##value", &position.x, 0.05f))
        {
            transform.setPosition(position);
        }
        grid.endRow();

        glm::vec3 rotation = degrees(transform.getRotation());
        grid.nextRow("Rotation");
        if (ImGui::DragFloat3("##value", &rotation.x, 0.1f))
        {
            transform.setRotation(radians(rotation));
        }
        grid.endRow();

        glm::vec3 scale = transform.getScale();
        grid.nextRow("Scale");
        if (ImGui::DragFloat3("##value", &scale.x, 0.025f))
        {
            transform.setScale(scale);
        }
        grid.endRow();
    }

    template<>
    void PropertiesWindow::drawComponent<Tag>(ECS::Entity entity)
    {
        auto& tag = entity.get<Tag>();

        drawComponentTitle("Tag");

        PropertyGrid grid("##TagGrid");
        if (!grid.isOpen())
        {
            return;
        }

        grid.nextRow("Name");
        ImGui::InputText("##value", &tag.name);
        grid.endRow();
    }

    template<>
    void PropertiesWindow::drawComponent<Camera>(ECS::Entity entity)
    {
        auto& camera = entity.get<Camera>();

        drawComponentTitle("Camera");

        PropertyGrid grid("##CameraGrid");
        if (!grid.isOpen())
        {
            return;
        }

        grid.nextRow("Background");
        ImGui::ColorEdit4("##value", &camera.bgColor.x);
        grid.endRow();

        float fov = camera.getFov();
        grid.nextRow("FOV");
        if (ImGui::DragFloat("##value", &fov, 0.1f, 1.0f, 179.0f, "%.2f"))
        {
            camera.setFov(fov);
        }
        grid.endRow();

        float nearClip = camera.getNear();
        grid.nextRow("Near");
        if (ImGui::DragFloat("##value", &nearClip, 0.01f, 0.0001f, 10000.0f, "%.4f"))
        {
            camera.setNear(nearClip);
        }
        grid.endRow();

        float farClip = camera.getFar();
        grid.nextRow("Far");
        if (ImGui::DragFloat("##value", &farClip, 1.0f, 0.01f, 1000000.0f, "%.2f"))
        {
            camera.setFar(farClip);
        }
        grid.endRow();

        float aspectRatio = camera.getAspectRatio();
        grid.nextRow("Aspect");
        if (ImGui::DragFloat("##value", &aspectRatio, 0.01f, 1, 16384))
        {
            camera.setAspectRatio(aspectRatio);
        }
        grid.endRow();

    }

    template<>
    void PropertiesWindow::drawComponent<PointLight>(ECS::Entity entity)
    {
        auto& pointLight = entity.get<PointLight>();

        drawComponentTitle("Point Light");

        PropertyGrid grid("##PointLightGrid");
        if (!grid.isOpen())
        {
            return;
        }

        grid.nextRow("Color");
        if (ImGui::ColorEdit3("##value", &pointLight.color.x))
        {
        }
        grid.endRow();

        grid.nextRow("Power");
        ImGui::DragFloat("##value", &pointLight.power, 0.05f, 0.0f, 100000.0f, "%.2f");
        grid.endRow();
    }

    template<>
    void PropertiesWindow::drawComponent<MeshRenderer>(ECS::Entity entity)
    {
        const auto& meshRenderer = entity.get<MeshRenderer>();

        drawComponentTitle("Mesh Renderer");

        PropertyGrid grid("##MeshRendererGrid");
        if (!grid.isOpen())
        {
            return;
        }

        grid.nextRow("Mesh");
        ImGui::TextUnformatted(meshRenderer.mesh ? "<Assigned>" : "<None>");
        grid.endRow();

        const AssetRef<MaterialShader> material = meshRenderer.getMaterial();

        grid.nextRow("Material");
        ImGui::TextUnformatted(material ? "<Assigned>" : "<None>");
        grid.endRow();
    }

    template<>
    void PropertiesWindow::drawAssetType<Mesh>(const AssetID asset)
    {
        AssetManager& assetManager = Engine::getAssetManager();
        const AssetRef<Mesh> mesh = assetManager.getAsset<Mesh>(asset);

        drawComponentSpacing();

        ImGui::Text("Vectex count: %ld", mesh->getVertexCount());
        ImGui::Text("Index count: %ld", mesh->getIndexCount());
    }
}
