#pragma once
#include <memory>
#include <vector>

#include "core/system.h"
#include "rendering/window.h"

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

        void exit();


        // TODO wait for safe time to add systems
        template <typename T, typename... Args>
        void registerSystem(Args&&... args)
        {
            T* system = new T(std::forward<Args>(args)...);
            registeredSystems.push_back(system);
        }
    private:
        std::vector<System*> registeredSystems;
        EngineConfig config;

        bool running = true;
    };
}
