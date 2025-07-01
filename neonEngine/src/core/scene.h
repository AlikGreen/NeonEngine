#pragma once
#include "asset/asset.h"
#include "ecs/world.h"

namespace Neon
{
class Scene final : public Asset
{
public:
    World& getWorld();
private:
    World* world = new World();
};
}
