#include "engine.h"

#include <graphics/loaders/imageLoader.h>
#include <graphics/loaders/prefabLoaderGLB.h>
#include <graphics/loaders/shaderLoader.h>

#include "coreSystem.h"
#include "graphics/renderSystem.h"

#include "eventManager.h"
#include "sceneManager.h"
#include "audio/audioManager.h"
#include "asset/assetManager.h"

namespace Neon
{
    Box<EventManager> Engine::eventManager;
    Box<AssetManager> Engine::assetManager;
    Box<AudioManager> Engine::audioManager;
    Box<SceneManager> Engine::sceneManager;

    bool Engine::running = false;
    float Engine::deltaTime = 0.0f;
    std::vector<Box<System>> Engine::registeredSystems{};
    EngineConfig Engine::config;

    void Engine::initialize(const EngineConfig &config)
    {
        Log::init("Neon Engine");

        Engine::config = config;
        eventManager = makeBox<EventManager>();
        assetManager = makeBox<AssetManager>();
        audioManager = makeBox<AudioManager>();
        sceneManager = makeBox<SceneManager>();

        getAssetManager().registerLoader<PrefabLoaderGLB, Prefab>({".glb", ".bin", ".gltf"});
        getAssetManager().registerLoader<ImageLoader, Image>({".png", ".jpg", ".jpeg", ".bmp", ".hdr", ".ppm"});
        getAssetManager().registerLoader<ShaderLoader, Rc<RHI::Shader>>({".glsl", ".shader"});
    }

    void Engine::quit()
    {
        running = false;
    }

    EngineConfig Engine::getConfig()
    {
        return config;
    }

    const std::vector<Box<System>>& Engine::getSystems()
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

    SceneManager& Engine::getSceneManager()
    {
        return *sceneManager;
    }

    float Engine::getDeltaTime()
    {
        return deltaTime;
    }

    void Engine::run()
    {
        startup();

        running = true;
        while (running)
        {
            auto start = std::chrono::high_resolution_clock::now();

            eventManager->handleEvents();

            for (const auto& system: registeredSystems)
            {
                system->preUpdate();
            }

            for (const auto& system: registeredSystems)
            {
                system->update();
            }

            for (const auto& system: registeredSystems)
            {
                system->postUpdate();
            }

            for (const auto& system: registeredSystems)
            {
                system->preRender();
            }

            for (const auto& system: registeredSystems)
            {
                system->render();
            }

            for (const auto& system: registeredSystems)
            {
                system->postRender();
            }

            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<float> diff = end - start;
            deltaTime = diff.count();
        }

        shutdown();
    }

    void Engine::startup()
    {

        for (const auto& system: registeredSystems)
        {
            system->preStartup();
        }

        for (const auto& system: registeredSystems)
        {
            system->startup();
        }

        for (const auto& system: registeredSystems)
        {
            system->postStartup();
        }
    }

    void Engine::shutdown()
    {
        for (const auto& system: registeredSystems)
        {
            system->shutdown();
        }
    }
}
