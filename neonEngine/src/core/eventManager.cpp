#include "eventManager.h"

#include "core/engine.h"

namespace Neon
{
    void EventManager::handleEvents()
    {
        for(const auto event : events)
        {
            for(const auto system : Engine::getSystems())
            {
                system->event(event);

                if(event->isCanceled())
                    break;
            }
        }

        events.clear();
    }
}
