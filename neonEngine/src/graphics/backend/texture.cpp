#include "texture.h"

#include "core/engine.h"
#include "physicalDevice.h"
#include "graphics/renderSystem.h"

namespace Neon
{
    Texture::Texture(const TextureType type, const TextureFormat format, const int width, const int height, TextureUsage usage)
    {
        const RenderSystem* renderSystem = Engine::getSystem<RenderSystem>();
        device = renderSystem->getDevice();

        SDL_GPUTextureCreateInfo createInfo{};
        createInfo.type        = ConvertSDL::textureTypeToSDL(type);
        createInfo.format      = ConvertSDL::textureFormatToSDL(format);
        createInfo.width       = width;
        createInfo.height      = height;
        createInfo.layer_count_or_depth = 1;
        createInfo.num_levels = 1;
        createInfo.usage       = static_cast<Uint32>(usage);

        handle = SDL_CreateGPUTexture(*device, &createInfo);
    }

    Texture::Texture(SDL_GPUTexture *existing) : handle(existing)
    {
        device = Engine::getSystem<RenderSystem>()->getDevice();
    }

    Texture::operator SDL_GPUTexture*() const
    {
        return handle;
    }

    SDL_GPUTexture * Texture::getHandle() const
    {
        return handle;
    }
}
