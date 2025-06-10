#pragma once
#include "glm/vec3.hpp"

namespace Neon
{
class Material : public Asset
{
public:
    float roughness;
    float metalness;
    glm::vec4 albedo;
};
}
