#include "image.h"

#include "asset/assetHandle.h"

namespace Neon
{
    Image::Image(const AssetHandle texture, const AssetHandle sampler) : texture(texture), sampler(sampler) {  }

    NRHI::Texture* Image::getTexture() const
    {
        return texture.get();
    }

    NRHI::Sampler* Image::getSampler() const
    {
        return sampler.get();
    }
}
