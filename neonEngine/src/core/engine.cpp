#include "engine.h"

#include <iostream>

#include "ecs/ecsSystem.h"
#include "graphics/renderSystem.h"

namespace Neon
{
    Engine* Engine::instance = nullptr;

    Engine::Engine(const EngineConfig &config)
    {
        this->config = config;
        this->eventManager = new EventManager();
        instance = this;
    }

    void Engine::startup()
    {
        registerSystem<RenderSystem>(config.windowOptions);
        registerSystem<ECSSystem>();

        for (const auto system: registeredSystems)
        {
            system->preStartup();
        }

        for (const auto system: registeredSystems)
        {
            system->startup();
        }

        for (const auto system: registeredSystems)
        {
            system->postStartup();
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

    EventManager* Engine::getEventManager() const
    {
        return eventManager;
    }

    Engine* Engine::getInstance()
    {
        return instance;
    }

    std::vector<System *> Engine::getSystems()
    {
        return registeredSystems;
    }

    void Engine::run()
    {
        while (running)
        {
            for (const auto system: registeredSystems)
            {
                system->preUpdate();
            }

            eventManager->handleEvents();

            for (const auto system: registeredSystems)
            {
                system->update();
            }

            eventManager->handleEvents();

            for (const auto system: registeredSystems)
            {
                system->postUpdate();
            }

            eventManager->handleEvents();

            for (const auto system: registeredSystems)
            {
                system->preRender();
            }

            eventManager->handleEvents();

            for (const auto system: registeredSystems)
            {
                system->render();
            }

            eventManager->handleEvents();

            for (const auto system: registeredSystems)
            {
                system->postRender();
            }

            eventManager->handleEvents();
        }
    }
}
