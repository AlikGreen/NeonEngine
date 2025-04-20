#include "eventManager.h"

#include "../neonEngine.h"

namespace Neon
{
    void EventManager::handleEvents()
    {
        for(const auto event : events)
        {
            for(const auto system : Engine::getInstance()->getSystems())
            {
                system->event(event);

                if(event->isCanceled())
                    break;
            }
        }

        events.clear();
    }
}
