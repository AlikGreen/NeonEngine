#pragma once
#include "sampler.h"
#include "texture.h"
#include "asset/assetRef.h"

namespace Neon
{
class Image
{
public:
    Image(const Rc<RHI::Texture>& texture, const Rc<RHI::Sampler>& sampler);

    AssetRef<Rc<RHI::Texture>> texture;
    AssetRef<Rc<RHI::Sampler>> sampler;
};
}
