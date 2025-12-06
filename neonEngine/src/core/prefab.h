#pragma once

#include <neonECS/neonECS.h>

#include "scene.h"

namespace Neon
{
struct PrefabComponent
{
    uint32_t temp{};
};

class Prefab
{
public:
    Scene scene{};
};
}
