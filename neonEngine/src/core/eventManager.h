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
