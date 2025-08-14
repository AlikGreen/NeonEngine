#pragma once
#include "sampler.h"
#include "texture.h"
#include "asset/assetHandle.h"
#include "asset/assetRef.h"

namespace Neon
{
class Image
{
public:
    Image(AssetHandle texture, AssetHandle sampler);

    [[nodiscard]] Ref<NRHI::Texture> getTexture() const;
    [[nodiscard]] Ref<NRHI::Sampler> getSampler() const;
private:
    AssetRef<NRHI::Texture> texture;
    AssetRef<NRHI::Sampler> sampler;
};
}
