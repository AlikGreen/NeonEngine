
#include "editorSystem.h"
#include "core/coreSystem.h"
#include "core/engine.h"
#include "graphics/imGuiSystem.h"
#include "graphics/renderSystem.h"
#include "input/inputSystem.h"
#include "windows/assetsWindow.h"
#include "windows/propertiesWindow.h"
#include "windows/sceneGraphWindow.h"


int main()
{
    Neon::EngineConfig config;
    config.windowOptions.title = "Sandbox App";
    config.windowOptions.vsync = false;

    config.engineResourcesPath = R"(C:\Users\alikg\CLionProjects\neonEngine\neonEngine\resources)";
    config.gameResourcesPath = R"(C:\Users\alikg\CLionProjects\neonEngine\sandboxApp\resources)";

    Neon::Engine::initialize(config);

    Neon::Engine::registerSystem<Neon::CoreSystem>();
    Neon::Engine::registerSystem<Neon::GraphicsSystem>(config.windowOptions);
    Neon::Engine::registerSystem<Neon::RenderSystem>();
    Neon::Engine::registerSystem<Neon::ImGuiSystem>();

    Neon::Engine::registerSystem<Neon::InputSystem>();

    Neon::Engine::registerSystem<Neon::Editor::EditorSystem>();

    Neon::Engine::run();
}
