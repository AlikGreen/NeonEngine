#pragma once
#include <cstdint>

#include "graphics/api/enums/mipmapFilter.h"
#include "graphics/api/enums/textureFilter.h"
#include "graphics/api/enums/textureFormat.h"
#include "graphics/api/enums/textureUsage.h"
#include "graphics/api/enums/textureWrap.h"

namespace Neon
{
struct TextureDescription
{
    uint32_t width = 0;
    uint32_t height = 0;
    uint32_t depth = 0;

    TextureFilter minFilter = TextureFilter::Linear;
    TextureFilter magFilter = TextureFilter::Linear;
    MipmapFilter mipmapFilter = MipmapFilter::Linear;

    TextureFormat format = TextureFormat::R8G8B8A8Unorm;
    TextureUsage usage = TextureUsage::Sampler;

    uint32_t numMipmaps = 1;

    struct WrapMode
    {
        TextureWrap x = TextureWrap::Repeat;
        TextureWrap y = TextureWrap::Repeat;
        TextureWrap z = TextureWrap::Repeat;
    };

    WrapMode wrapMode = WrapMode{};
};
}
