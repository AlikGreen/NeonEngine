#pragma once
#include <neonRHI/neonRHI.h>

#include "glm/vec3.hpp"

#include "asset/assetRef.h"
#include "graphics/image.h"
#include "graphics/materialShader.h"

namespace Neon
{
class PBRMaterial final : public MaterialShader
{
public:
    PBRMaterial();

    std::string name = "material";

    float alphaCutoff = 0.0f;
    bool doubleSided = false;

    glm::vec4 albedo = glm::vec4(1.0f);
    AssetRef<Image> albedoTexture = nullptr;

    float roughness = 1.0f;
    float metalness = 0.0f;
    AssetRef<Image> metallicRoughnessTexture = nullptr;

    glm::vec3 emission = glm::vec3(0.0f);
    AssetRef<Image> emissionTexture = nullptr;

    float normalTextureStrength = 1.0f;
    AssetRef<Image> normalTexture = nullptr;

    float occlusionTextureStrength = 1.0f;
    AssetRef<Image> occlusionTexture = nullptr;
};
}
