#pragma once
#include "core/system.h"
#include "windows/assetsWindow.h"
#include "windows/gameWindow.h"
#include "windows/propertiesWindow.h"
#include "windows/sceneGraphWindow.h"
#include "windows/editorViewportWindow.h"

namespace Neon::Editor
{
    struct ComponentInfo
    {
        std::string name;
        std::function<void(ECS::Entity entity)> emplaceCallback;
    };

    class EditorSystem final : public System
    {
    public:
        void startup() override;
        void update() override;
        void event(Event *event) override;

        template<typename T>
        void registerComponent(const std::string& name)
        {
            registeredComponents.emplace_back(name, [](ECS::Entity entity){ entity.emplace<T>(); });
        }
        std::vector<ComponentInfo> getComponents();

        EditorViewportWindow editorViewport{};
        GameWindow viewportWindow{};
        AssetsWindow assetsWindow{};
        PropertiesWindow propertiesWindow{};
        SceneGraphWindow sceneGraphWindow{};

    private:
        std::vector<ComponentInfo> registeredComponents{};
    };
}
