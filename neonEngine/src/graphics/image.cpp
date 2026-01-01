#include "image.h"

namespace Neon
{
    Image::Image(const Rc<RHI::Texture>& texture, const Rc<RHI::Sampler>& sampler)
    {
        AssetManager& assetManager = Engine::getAssetManager();

        this->texture = assetManager.addAsset(texture);
        this->sampler = assetManager.addAsset(sampler);
    }
}
