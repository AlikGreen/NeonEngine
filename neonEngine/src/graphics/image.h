#pragma once
#include <tiny_gltf.h>

#include "sampler.h"
#include "spirv_common.hpp"
#include "texture.h"
#include "asset/assetRef.h"
#include "assets/textureData.h"

namespace Neon
{
class Image
{
public:
    Image(const Rc<RHI::Texture>& texture, const Rc<RHI::Sampler>& sampler);
    Image(const AssetRef<TextureData> &data, Rc<RHI::Sampler> sampler = nullptr);

    Rc<RHI::Texture> texture;
    Rc<RHI::Sampler> sampler;
};
}
