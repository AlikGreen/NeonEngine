#include "colorTarget.h"

#include "texture.h"

namespace Neon
{
    ColorTarget::ColorTarget(Texture texture) : texture(texture)
    {

    }

    ColorTarget::operator SDL_GPUColorTargetInfo() const
    {
        SDL_GPUColorTargetInfo targetInfo{};
        targetInfo.texture = texture;
        targetInfo.store_op = ConvertSDL::storeOpToSDL(storeOperation);
        targetInfo.load_op = ConvertSDL::loadOpToSDL(loadOperation);
        targetInfo.clear_color = {clearColor.r, clearColor.g, clearColor.b, clearColor.a};

        return targetInfo;
    }
}
