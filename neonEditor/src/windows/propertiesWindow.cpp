#include "propertiesWindow.h"

#include "sceneGraphWindow.h"
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
    PropertiesWindow::PropertiesWindow()
        : ImGuiWindow("Properties") {  }

    void PropertiesWindow::render()
    {
        Rc<SceneGraphWindow> sceneGraphWindow = Engine::getSystem<ImGuiSystem>()->getWindow<SceneGraphWindow>();

        std::optional<ECS::Entity> optEntity = sceneGraphWindow->getSelectedEntity();

        if(!optEntity.has_value())
            return;

        ECS::Entity selected = optEntity.value();

        ImGui::Spacing();
        if (selected.has<Tag>())
        {
            drawComponentSpacing();
            drawComponent<Tag>(selected);
        }
        if (selected.has<Transform>())
        {
            drawComponentSpacing();
            drawComponent<Transform>(selected);
        }
        if (selected.has<Camera>())
        {
            drawComponentSpacing();
            drawComponent<Camera>(selected);
        }
        if (selected.has<PointLight>())
        {
            drawComponentSpacing();
            drawComponent<PointLight>(selected);
        }
        if (selected.has<MeshRenderer>())
        {
            drawComponentSpacing();
            drawComponent<MeshRenderer>(selected);
        }

        drawComponentSpacing();
    }

    void PropertiesWindow::drawComponentSpacing()
    {
        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();
    }

    template<>
    void PropertiesWindow::drawComponent<Transform>(ECS::Entity entity)
    {
        auto& transform = entity.get<Transform>();

        ImGui::TextUnformatted("Transform");
        ImGui::Spacing();

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

        glm::vec3 rotation = transform.getRotation();
        grid.nextRow("Rotation");
        if (ImGui::DragFloat3("##value", &rotation.x, 0.02f))
        {
            transform.setRotation(rotation);
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

        ImGui::TextUnformatted("Tag");
        ImGui::Spacing();

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

        ImGui::TextUnformatted("Camera");
        ImGui::Spacing();

        PropertyGrid grid("##CameraGrid");
        if (!grid.isOpen())
        {
            return;
        }

        grid.nextRow("Match Window Size");
        ImGui::Checkbox("##value", &camera.matchWindowSize);
        grid.endRow();

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

        if (!camera.matchWindowSize)
        {
            int width = static_cast<int>(camera.getWidth());
            int height = static_cast<int>(camera.getHeight());

            grid.nextRow("Width");
            if (ImGui::DragInt("##value", &width, 1.0f, 1, 16384))
            {
                camera.setWidth(static_cast<uint32_t>(width));
            }
            grid.endRow();

            grid.nextRow("Height");
            if (ImGui::DragInt("##value", &height, 1.0f, 1, 16384))
            {
                camera.setHeight(static_cast<uint32_t>(height));
            }
            grid.endRow();
        }
    }

    template<>
    void PropertiesWindow::drawComponent<PointLight>(ECS::Entity entity)
    {
        auto& pointLight = entity.get<PointLight>();

        ImGui::TextUnformatted("Point Light");
        ImGui::Spacing();

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

        ImGui::TextUnformatted("Mesh Renderer");
        ImGui::Spacing();

        PropertyGrid grid("##MeshRendererGrid");
        if (!grid.isOpen())
        {
            return;
        }

        grid.nextRow("Mesh");
        ImGui::TextUnformatted(meshRenderer.mesh ? "<Assigned>" : "<None>");
        grid.endRow();

        const AssetRef<Material> material = meshRenderer.getMaterial();

        grid.nextRow("Material");
        ImGui::TextUnformatted(material ? "<Assigned>" : "<None>");
        grid.endRow();
    }
}
