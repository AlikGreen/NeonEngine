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
    static RHI::PixelFormat getPixelFormatFromExtension(const std::string &extension);
    static RHI::PixelType getPixelTypeFromExtension(const std::string &extension);
    static RHI::TextureFormat getOptimalFormat(const std::string& extension, int channels);
};
}
