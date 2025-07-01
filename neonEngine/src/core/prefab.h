#pragma once

#include "asset/asset.h"
#include "ecs/world.h"

namespace Neon
{
struct PrefabComponent
{
    uint32_t temp{};
};

class Prefab final : public Asset
{
public:
    World world{};
};
}
