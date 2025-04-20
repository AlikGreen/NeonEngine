#pragma once
#include <concepts>
#include <vector>

#include "event.h"

namespace Neon
{
class EventManager
{
public:
    EventManager() = default;

    // Template function using the concept
    template <DerivedFromEvent T>
    void queueEvent(T* event)
    {
        events.push_back(event);
    }

    void handleEvents();
private:
    std::vector<Event*> events { };
};
}
