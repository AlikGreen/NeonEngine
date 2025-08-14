#pragma once
#include "ecs/world.h"

namespace Neon
{
class Scene
{
public:
    World& getWorld();
private:
    World* world = new World();
};
}
