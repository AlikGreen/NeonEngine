#pragma once

#include "ecs/world.h"

namespace Neon
{
struct PrefabComponent
{
    uint32_t temp{};
};

class Prefab
{
public:
    World world{};
};
}
