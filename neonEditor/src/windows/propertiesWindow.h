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
    void view(ECS::Entity entity);
    void view(AssetID asset);
    void stopViewing();
private:
    enum class LastSelected { None, Asset, Entity };
    void drawEntity(ECS::Entity entity);
    void drawAsset(AssetID asset);

    template<typename T>
    void drawAssetType(AssetID asset)
    {
        ;
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
    std::optional<ECS::Entity> m_latestEntity;
    std::optional<AssetID> m_latestAsset;
};

template<> void PropertiesWindow::drawComponent<Transform>(ECS::Entity entity);
template<> void PropertiesWindow::drawComponent<Tag>(ECS::Entity entity);
template<> void PropertiesWindow::drawComponent<Camera>(ECS::Entity entity);
template<> void PropertiesWindow::drawComponent<PointLight>(ECS::Entity entity);
template<> void PropertiesWindow::drawComponent<MeshRenderer>(ECS::Entity entity);

template<> void PropertiesWindow::drawAssetType<Mesh>(AssetID asset);
}
