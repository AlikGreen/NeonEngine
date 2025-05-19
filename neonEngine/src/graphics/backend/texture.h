#pragma once
#include <type_traits>
#include <SDL3/SDL.h>

namespace Neon
{
    enum class TextureFormat;
    enum class TextureType ;
    enum class TextureUsage : uint32_t;

    class PhysicalDevice;
    class Texture
    {
    public:
        Texture(TextureType type, TextureFormat format, int width, int height, TextureUsage usage);
        explicit Texture(SDL_GPUTexture* existing);

        operator SDL_GPUTexture*() const;
        [[nodiscard]] SDL_GPUTexture* getHandle() const;
    private:
        SDL_GPUTexture* handle;
        PhysicalDevice* device = nullptr;
    };
}
