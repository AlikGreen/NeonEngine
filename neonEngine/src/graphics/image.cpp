#include "image.h"

#include "asset/assetHandle.h"

namespace Neon
{
    Image::Image(const AssetHandle texture, const AssetHandle sampler) : texture(texture), sampler(sampler) {  }

    Ref<NRHI::Texture> Image::getTexture() const
    {
        return texture.get();
    }

    Ref<NRHI::Sampler> Image::getSampler() const
    {
        return sampler.get();
    }
}
