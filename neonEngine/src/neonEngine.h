#pragma once
#include <memory>
#include <vector>

#include "core/system.h"
#include "graphics/backend/window.h"

namespace Neon
{
    struct EngineConfig
    {
        WindowOptions windowOptions;
    };

    class Engine
    {
    public:
        explicit Engine(const EngineConfig &config);
        void startup();
        void run();
        void shutdown();

        void quit();

        // TODO wait for safe time to add systems
        template <typename T, typename... Args>
        void registerSystem(Args&&... args)
        {
            T* system = new T(std::forward<Args>(args)...);
            registeredSystems.push_back(system);
        }

        static Engine* getInstance();

        template <typename T>
        T* getSystem()
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
    private:
        std::vector<System*> registeredSystems;
        EngineConfig config;

        bool running = true;

        static Engine* instance;
    };
}
