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
        RHI::WindowCreationOptions windowOptions;
    };

    class Engine
    {
    public:
        static void initialize(const EngineConfig &config);
        static void run();

        static void quit();

        template <typename T, typename... Args>
        static void registerSystem(Args&&... args)
        {
            T* system = new T(std::forward<Args>(args)...);
            registeredSystems.push_back(system);
        }

        // template <typename T>
        // static void unregisterSystems()
        // {
        //     for (size_t i = 0; i < registeredSystems.size(); )
        //     {
        //         if (typeid(*registeredSystems[i]) == typeid(T))
        //         {
        //             delete registeredSystems[i];
        //             registeredSystems.erase(registeredSystems.begin() + i);
        //             // Don't increment i, since elements shift down
        //         }
        //         else
        //         {
        //             ++i;
        //         }
        //     }
        // }

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
        static Box<EventManager> eventManager;
        static Box<AssetManager> assetManager;
        static Box<AudioManager> audioManager;
        static Box<SceneManager> sceneManager;

        static std::vector<System*> registeredSystems;
        static EngineConfig config;

        static void shutdown();
        static void startup();

        static bool running;
    };
}
