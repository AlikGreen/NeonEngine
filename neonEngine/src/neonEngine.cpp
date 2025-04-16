#include "neonEngine.h"

#include <iostream>

#include "rendering/renderSystem.h"

namespace Neon
{
    Engine* Engine::instance = nullptr;

    Engine::Engine(const EngineConfig &config)
    {
        this->config = config;
        instance = this;
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

    void Engine::quit()
    {
        running = false;
    }

    Engine* Engine::getInstance()
    {
        return instance;
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
