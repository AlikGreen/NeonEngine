#pragma once
#include "graphics/api/enums/textureFormat.h"

namespace Neon
{
struct RenderTargetsDescription
{
    std::vector<TextureFormat> colorTargetFormats = {};
    TextureFormat depthTargetFormat = TextureFormat::Invalid;
};
}
