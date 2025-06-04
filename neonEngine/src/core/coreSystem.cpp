#include "coreSystem.h"

#include "engine.h"
#include "graphics/events/QuitEvent.h"

namespace Neon
{
    void CoreSystem::event(Event *event)
    {
        if(auto* quitEvent = dynamic_cast<QuitEvent*>(event))
        {
            Engine::quit();
        }
    }
}
