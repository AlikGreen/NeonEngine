#include <iostream>

#include "gameSystem.h"
#include "core/coreSystem.h"
#include "core/engine.h"
#include "ecs/ecsSystem.h"
#include "graphics/renderSystem.h"

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
    Neon::Engine::registerSystem<Neon::ECSSystem>();
    Neon::Engine::registerSystem<GameSystem>();

    Neon::Engine::startup();
    Neon::Engine::run();
    Neon::Engine::shutdown();
}
