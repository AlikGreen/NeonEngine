#pragma once
#include "asset/assetLoader.h"
#include "graphics/image.h"

namespace Neon
{
class ImageLoader final : public AssetLoader
{
public:
    void* load(const std::string &filePath) override;
private:
    static RHI::PixelType getPixelTypeFromExtension(const std::string &extension);
    static RHI::PixelFormat getOptimalFormat(const std::string& extension, int channels);
};
}
