#pragma once
#include <optional>
#include <vector>

#include "convertSDL.h"
#include "texture.h"

namespace Neon
{
    struct RenderTargetsDescription
    {
        std::vector<TextureFormat> colorTargetFormats = {};
        TextureFormat depthTargetFormat = TextureFormat::Invalid;
    };
}
