#include "texture.h"

namespace Neon {
    Texture::Texture(SDL_GPUTexture *existing) : handle(existing)
    {
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
