#include "image.h"

#include "asset/assetHandle.h"

namespace Neon
{
    Image::Image(const Rc<RHI::Texture>& texture, const Rc<RHI::Sampler>& sampler)
    {
        AssetManager& assetManager = Engine::getAssetManager();

        textureHandle = assetManager.addAsset(texture);
        samplerHandle = assetManager.addAsset(sampler);
    }

    Rc<RHI::Texture> Image::getTexture() const
    {
        return *textureHandle;
    }

    Rc<RHI::Sampler> Image::getSampler() const
    {
        return *samplerHandle;
    }
}
