#pragma once
#include "glm/vec3.hpp"

#include "asset/asset.h"

namespace Neon
{
class Material final : public Asset
{
public:
    float roughness = 1.0f;
    float metalness = 0.0f;
    glm::vec4 albedo = glm::vec4(1.0f);
};
}
