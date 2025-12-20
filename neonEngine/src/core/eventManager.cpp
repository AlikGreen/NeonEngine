#include "eventManager.h"

#include <ranges>

#include "core/engine.h"

namespace Neon
{
    void EventManager::handleEvents()
    {
        for(const auto event : events)
        {
            for (const auto system : std::ranges::reverse_view(Engine::getSystems()))
            {
                system->event(event);

                if(event->isCanceled())
                    break;
            }
        }

        for(const auto event : events)
        {
            delete event;
        }

        events.clear();
    }
}
