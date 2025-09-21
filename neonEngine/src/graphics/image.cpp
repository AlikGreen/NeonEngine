#include "image.h"

#include "asset/assetHandle.h"

namespace Neon
{
    Image::Image(RHI::Texture* texture, RHI::Sampler* sampler)
    {
        AssetManager& assetManager = Engine::getAssetManager();

        textureHandle = assetManager.addAsset(texture);
        samplerHandle = assetManager.addAsset(sampler);
    }

    RHI::Texture* Image::getTexture() const
    {
        return textureHandle.get();
    }

    RHI::Sampler* Image::getSampler() const
    {
        return samplerHandle.get();
    }
}
