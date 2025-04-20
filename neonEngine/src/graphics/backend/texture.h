#pragma once
#include <SDL3/SDL.h>

namespace Neon
{
class Texture
{
public:
    explicit Texture(SDL_GPUTexture* existing);

    operator SDL_GPUTexture*() const;
    [[nodiscard]] SDL_GPUTexture* getHandle() const;
private:
    SDL_GPUTexture* handle;
};
}
