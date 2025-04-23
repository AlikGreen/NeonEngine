#pragma once
#include <memory>

#include "world.h"
#include "core/system.h"

namespace Neon
{
class ECSSystem final : public System
{
public:
    std::shared_ptr<World> getWorld();
private:
    std::shared_ptr<World> world = std::make_shared<World>();
};
}
