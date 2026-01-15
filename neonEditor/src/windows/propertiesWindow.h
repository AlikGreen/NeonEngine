#pragma once
#include <imgui.h>
#include <optional>

#include "editorWindow.h"
#include "core/components/tagComponent.h"
#include "core/components/transformComponent.h"
#include "graphics/components/camera.h"
#include "graphics/components/meshRenderer.h"
#include "graphics/components/pointLight.h"


namespace Neon::Editor
{
class PropertiesWindow final : public EditorWindow
{
public:
    void render() override;
    void event(Event *event) override;
private:
    enum class LastSelected { None, Asset, Entity };
    void drawEntity(ECS::Entity entity);
    void drawAsset(AssetID asset);

    template<typename T>
    void drawAssetType(AssetID asset)
    {

    }

    template<typename T>
    void drawComponent(const ECS::Entity entity)
    {
        if(entity.has<T>())
            ImGui::Text(typeid(T).name());
    }

    static void drawComponentSpacing();
    static void drawComponentTitle(const char *text);

    LastSelected m_latestViewedType = LastSelected::None;
    std::string m_renameString;
    std::optional<std::variant<ECS::Entity, AssetID>> m_currentInspected;
};

template<> void PropertiesWindow::drawComponent<Transform>(ECS::Entity entity);
template<> void PropertiesWindow::drawComponent<Tag>(ECS::Entity entity);
template<> void PropertiesWindow::drawComponent<Camera>(ECS::Entity entity);
template<> void PropertiesWindow::drawComponent<PointLight>(ECS::Entity entity);
template<> void PropertiesWindow::drawComponent<MeshRenderer>(ECS::Entity entity);

template<> void PropertiesWindow::drawAssetType<Mesh>(AssetID asset);
template<> void PropertiesWindow::drawAssetType<MaterialShader>(AssetID asset);
}
