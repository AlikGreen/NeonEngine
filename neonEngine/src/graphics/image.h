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
    Image(RHI::Texture* texture, RHI::Sampler* sampler);

    [[nodiscard]] RHI::Texture* getTexture() const;
    [[nodiscard]] RHI::Sampler* getSampler() const;
private:
    AssetRef<RHI::Texture> textureHandle;
    AssetRef<RHI::Sampler> samplerHandle;
};
}
