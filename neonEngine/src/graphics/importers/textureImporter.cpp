#include "textureImporter.h"

#include <stb_image.h>
#include <filesystem>
#include <algorithm>

#include "debug.h"
#include "graphics/assets/textureData.h"

namespace Neon
{
    RHI::PixelType getPixelTypeFromExtension(const std::string &extension)
    {
        if (extension == "exr" || extension == "hdr")
            return RHI::PixelType::Float;

        return RHI::PixelType::UnsignedByte;
    }

    void* TextureImporter::load(const std::string &filepath)
    {
        std::string ext = std::filesystem::path(filepath).extension().string();
        std::ranges::transform(ext, ext.begin(), tolower);

        if (!ext.empty() && ext[0] == '.')
            ext = ext.substr(1);

        int w, h, channels;
        void *pixels{};

        stbi_set_flip_vertically_on_load(true);

        if (ext == "exr" || ext == "hdr")
            pixels = stbi_loadf(filepath.c_str(), &w, &h, &channels, 4);
        else
            pixels = stbi_load(filepath.c_str(), &w, &h, &channels, 4);

        Debug::ensure(pixels != nullptr, "Failed to load image {}\n", stbi_failure_reason());

        auto* texData = new TextureData();
        texData->width = w;
        texData->height = h;
        texData->pixelLayout = RHI::PixelLayout::RGBA;
        texData->pixelType = getPixelTypeFromExtension(ext);
        texData->data = pixels;
        return texData;
    }
}
