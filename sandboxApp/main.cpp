#include <iostream>

#include "gameSystem.h"
#include "neonEngine.h"

int main()
{
    Neon::EngineConfig config;
    config.windowOptions.title = "Sandbox App";

    auto engine = Neon::Engine(config);

    engine.registerSystem<GameSystem>();

    engine.startup();
    engine.run();
    engine.shutdown();
}