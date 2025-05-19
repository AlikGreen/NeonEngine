#pragma once

#include "world.h"
#include "core/system.h"

namespace Neon
{
class ECSSystem final : public System
{
public:
    Ref<World> getWorld();
private:
    Ref<World> world = makeRef<World>();
};
}
