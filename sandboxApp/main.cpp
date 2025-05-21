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

    auto engine = Neon::Engine(config);

    engine.registerSystem<GameSystem>();

    engine.startup();
    engine.run();
    engine.shutdown();
}