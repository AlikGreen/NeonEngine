#include "ECSSystem.h"

namespace Neon
{
    std::shared_ptr<World> ECSSystem::getWorld()
    {
        return world;
    }
}
