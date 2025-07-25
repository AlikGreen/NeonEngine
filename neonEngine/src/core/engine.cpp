#include "engine.h"

#include "coreSystem.h"
#include "graphics/renderSystem.h"

#include "eventManager.h"
#include "sceneManager.h"
#include "audio/audioManager.h"
#include "asset/assetManager.h"

namespace Neon
{
    Scope<EventManager> Engine::eventManager;
    Scope<AssetManager> Engine::assetManager;
    Scope<AudioManager> Engine::audioManager;
    Scope<SceneManager> Engine::sceneManager;

    bool Engine::running = false;
    std::vector<System*> Engine::registeredSystems = std::vector<System*>();
    EngineConfig Engine::config;

    void Engine::initialize(const EngineConfig &config)
    {
        Engine::config = config;
        eventManager = makeScope<EventManager>();
        assetManager = makeScope<AssetManager>();
        audioManager = makeScope<AudioManager>();
        sceneManager = makeScope<SceneManager>();
    }

    void Engine::startup()
    {
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


    EngineConfig Engine::getConfig()
    {
        return config;
    }

    std::vector<System *> Engine::getSystems()
    {
        return registeredSystems;
    }

    EventManager& Engine::getEventManager()
    {
        return *eventManager;
    }

    AssetManager& Engine::getAssetManager()
    {
        return *assetManager;
    }

    AudioManager& Engine::getAudioManager()
    {
        return *audioManager;
    }

    SceneManager & Engine::getSceneManager()
    {
        return *sceneManager;
    }

    void Engine::run()
    {
        running = true;
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
