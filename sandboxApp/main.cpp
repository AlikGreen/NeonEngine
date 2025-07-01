#include "gameSystem.h"
#include "asset/assetManager.h"
#include "core/coreSystem.h"
#include "core/engine.h"
#include "core/prefabSerializerGLB.h"
#include "graphics/renderSystem.h"
#include "input/inputSystem.h"


int main()
{
    Neon::EngineConfig config;
    config.windowOptions.title = "Sandbox App";
    config.windowOptions.vsync = false;

    config.engineResourcesPath = R"(C:\Users\alikg\CLionProjects\neonEngine\neonEngine\resources)";
    config.gameResourcesPath = R"(C:\Users\alikg\CLionProjects\neonEngine\sandboxApp\resources)";

    Neon::Engine::initialize(config);

    Neon::Engine::registerSystem<Neon::CoreSystem>();
    Neon::Engine::registerSystem<Neon::RenderSystem>(config.windowOptions);
    Neon::Engine::registerSystem<GameSystem>();
    Neon::Engine::registerSystem<Neon::InputSystem>();

    Neon::Engine::getAssetManager().registerSerializer<Neon::PrefabSerializerGLB>({".glb"});

    Neon::Engine::startup();
    Neon::Engine::run();
    Neon::Engine::shutdown();
}
