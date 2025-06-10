#pragma once
#include <memory>
#include <vector>

#include "asset/assetManager.h"
#include "audio/audioManager.h"
#include "core/system.h"
#include "core/eventManager.h"
#include "graphics/api/descriptions/windowCreationOptions.h"

namespace Neon
{
    struct EngineConfig
    {
        std::string engineResourcesPath;
        std::string gameResourcesPath;
        WindowCreationOptions windowOptions;
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
    private:
        static Scope<EventManager> eventManager;
        static Scope<AssetManager> assetManager;
        static Scope<AudioManager> audioManager;

        static std::vector<System*> registeredSystems;
        static EngineConfig config;

        static bool running;
    };
}
