#pragma once
#include "core/system.h"
#include "windows/assetsWindow.h"
#include "windows/propertiesWindow.h"
#include "windows/sceneGraphWindow.h"
#include "windows/viewportWindow.h"

namespace Neon::Editor
{
    class EditorSystem final : public System
    {
    public:
        void startup() override;
        void update() override;
        void event(Event *event) override;

        ViewportWindow viewportWindow{};
        AssetsWindow assetsWindow{};
        PropertiesWindow propertiesWindow{};
        SceneGraphWindow sceneGraphWindow{};
    };
}
