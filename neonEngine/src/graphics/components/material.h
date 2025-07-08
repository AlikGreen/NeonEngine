#pragma once
#include <graphics/api/texture.h>

#include "glm/vec3.hpp"

#include "asset/asset.h"
#include "asset/assetRef.h"

namespace Neon
{
class Material final : public Asset
{
public:
    const char* name = "material";

    float alphaCutoff = 0.0f;
    bool doubleSided = false;

    glm::vec4 albedo = glm::vec4(1.0f);
    AssetRef<Texture> albedoTexture = nullptr;

    float roughness = 1.0f;
    float metalness = 0.0f;
    AssetRef<Texture> metallicRoughnessTexture = nullptr;

    glm::vec3 emission = glm::vec3(0.0f);
    AssetRef<Texture> emissionTexture = nullptr;

    float normalTextureStrength = 1.0f;
    AssetRef<Texture> normalTexture = nullptr;

    float occlusionTextureStrength = 1.0f;
    AssetRef<Texture> occlusionTexture = nullptr;
};
}
