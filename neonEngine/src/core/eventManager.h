#pragma once
#include <vector>

#include "event.h"

namespace Neon
{
class EventManager
{
public:
    EventManager() = default;

    template<typename T, typename... Args>
    requires(std::is_base_of_v<Event, T>)
    void queueEvent(Args&&... args)
    {
        events.push_back(makeBox<T>(std::forward<Args>(args)...));
    }

    void handleEvents();
private:
    std::vector<Box<Event>> events { };
};
}
