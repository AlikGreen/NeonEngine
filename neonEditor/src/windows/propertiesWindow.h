#pragma once
#include <imgui.h>
#include <optional>

#include "../../../neonEngine/dependencies/neonecs/src/entity.h"
#include "core/components/tagComponent.h"
#include "core/components/transformComponent.h"
#include "graphics/components/camera.h"
#include "graphics/components/meshRenderer.h"
#include "graphics/components/pointLight.h"


namespace Neon::Editor
{
class PropertiesWindow final
{
public:
    void render();
private:
    template<typename T>
    void drawComponent(const ECS::Entity entity)
    {
        if(entity.has<T>())
            ImGui::Text(typeid(T).name());
    }

    static void drawComponentSpacing();
    static void drawComponentTitle(const char *text);

    std::string m_renameString;
    std::optional<ECS::Entity> m_entityLastFrame;
};

template<> void PropertiesWindow::drawComponent<Transform>(ECS::Entity entity);
template<> void PropertiesWindow::drawComponent<Tag>(ECS::Entity entity);
template<> void PropertiesWindow::drawComponent<Camera>(ECS::Entity entity);
template<> void PropertiesWindow::drawComponent<PointLight>(ECS::Entity entity);
template<> void PropertiesWindow::drawComponent<MeshRenderer>(ECS::Entity entity);
}
