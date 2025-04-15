#include "neonEngine.h"

#include <iostream>

#include "rendering/renderSystem.h"

namespace Neon
{
    Engine::Engine(const EngineConfig &config)
    {
        this->config = config;
    }

    void Engine::startup()
    {
        registerSystem<RenderSystem>(config.windowOptions);

        for (const auto system: registeredSystems)
        {
            system->startup();
        }
    }

    void Engine::shutdown()
    {
        for (const auto system: registeredSystems)
        {
            system->shutdown();
        }
    }

    void Engine::exit()
    {
        running = false;
    }

    void Engine::run()
    {
        while (running)
        {
            for (const auto system: registeredSystems)
            {
                system->preUpdate();
            }

            for (const auto system: registeredSystems)
            {
                system->update();
            }

            for (const auto system: registeredSystems)
            {
                system->postUpdate();
            }

            for (const auto system: registeredSystems)
            {
                system->preRender();
            }

            for (const auto system: registeredSystems)
            {
                system->render();
            }

            for (const auto system: registeredSystems)
            {
                system->postRender();
            }
        }
    }
}
