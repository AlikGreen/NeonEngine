#pragma once
#include <memory>
#include <vector>

#include <neonRHI/neonRHI.h>
#include "core/system.h"

namespace Neon
{
    class EventManager;
    class AssetManager;
    class AudioManager;
    class SceneManager;

    struct EngineConfig
    {
        std::string engineResourcesPath;
        std::string gameResourcesPath;
        NRHI::WindowCreationOptions windowOptions;
    };

    class Engine
    {
    public:
        static void initialize(const EngineConfig &config);
        static void startup();
        static void run();
        static void shutdown();

        static void quit();

        template <typename T, typename... Args>
        static void registerSystem(Args&&... args)
        {
            T* system = new T(std::forward<Args>(args)...);
            registeredSystems.push_back(system);
        }

        template <typename T>
        static T* getSystem()
        {
            for (System* system : registeredSystems)
            {
                if (system && typeid(*system) == typeid(T))
                {
                    return static_cast<T*>(system);
                }
            }
            return nullptr;
        }

        static EngineConfig getConfig();
        static std::vector<System*> getSystems();

        static EventManager& getEventManager();
        static AssetManager& getAssetManager();
        static AudioManager& getAudioManager();
        static SceneManager& getSceneManager();
    private:
        static Scope<EventManager> eventManager;
        static Scope<AssetManager> assetManager;
        static Scope<AudioManager> audioManager;
        static Scope<SceneManager> sceneManager;

        static std::vector<System*> registeredSystems;
        static EngineConfig config;

        static bool running;
    };
}
