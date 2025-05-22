#include <iostream>

#include "gameSystem.h"
#include "core/engine.h"

int main()
{
    Neon::EngineConfig config;
    config.windowOptions.title = "Sandbox App";
    config.windowOptions.vsync = false;

    config.engineResourcesPath = R"(C:\Users\alikg\CLionProjects\neonEngine\neonEngine\resources)";
    config.gameResourcesPath = R"(C:\Users\alikg\CLionProjects\neonEngine\sandboxApp\resources)";

    Neon::Engine::initialize(config);

    Neon::Engine::registerSystem<GameSystem>();

    Neon::Engine::startup();
    Neon::Engine::run();
    Neon::Engine::shutdown();
}