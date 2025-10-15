#include "imageLoader.h"

#include <stb_image.h>

#include "debug.h"
#include "graphics/renderSystem.h"


namespace Neon
{
    void* ImageLoader::load(const std::string &filePath)
    {
        std::string ext = std::filesystem::path(filePath).extension().string();
        std::ranges::transform(ext, ext.begin(), ::tolower);

        if (!ext.empty() && ext[0] == '.')
            ext = ext.substr(1);

        int w, h, channels;
        const void *pixels{};

        if (ext == "exr" || ext == "hdr")
            pixels = stbi_loadf(filePath.c_str(), &w, &h, &channels, 4);
        else
            pixels = stbi_load(filePath.c_str(), &w, &h, &channels, 4);

        Debug::ensure(pixels != nullptr, "Failed to load image %s\n", stbi_failure_reason());
        auto* device = Engine::getSystem<RenderSystem>()->getDevice();

        RHI::TextureDescription texDesc{};
        texDesc.dimensions.x = w;
        texDesc.dimensions.y = h;
        texDesc.format = getOptimalFormat(ext, channels);

        const auto texture = device->createTexture(texDesc);

        RHI::TextureUploadDescription uploadDesc{};

        uploadDesc.data = pixels;
        uploadDesc.pixelType = getPixelTypeFromExtension(ext);

        const auto cl = device->createCommandList();

        cl->begin();
        cl->updateTexture(texture, uploadDesc);

        device->submit(cl);

        constexpr RHI::SamplerDescription samplerDesc{};
        const auto sampler = device->createSampler(samplerDesc);

        return new Image(texture, sampler);
    }

    RHI::PixelType ImageLoader::getPixelTypeFromExtension(const std::string &extension)
    {
        if (extension == "exr" || extension == "hdr")
            return RHI::PixelType::Float;

        return RHI::PixelType::UnsignedByte;
    }

    RHI::PixelFormat ImageLoader::getOptimalFormat(const std::string& extension, const int channels)
    {
        if (extension == "hdr" || extension == "exr")
            return RHI::PixelFormat::R32G32B32A32Float;

        if (channels == 3) return RHI::PixelFormat::R8G8B8Unorm;

        return RHI::PixelFormat::R8G8B8A8Unorm;
    }
}