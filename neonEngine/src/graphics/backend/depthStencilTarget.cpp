#include "depthStencilTarget.h"

namespace Neon
{
    DepthStencilTarget::DepthStencilTarget(Texture texture) : texture(texture)
    {

    }

    DepthStencilTarget::operator SDL_GPUDepthStencilTargetInfo() const
    {
        SDL_GPUDepthStencilTargetInfo depthStencil = {
            .texture         = texture,
            .clear_depth     = 1.0f,                      // clear to far plane
            .load_op         = ConvertSDL::loadOpToSDL(loadOperation),
            .store_op        = ConvertSDL::storeOpToSDL(storeOperation),
            .stencil_load_op = SDL_GPU_LOADOP_DONT_CARE,
            .stencil_store_op= SDL_GPU_STOREOP_DONT_CARE,
            .cycle           = false,
            .clear_stencil   = 0,
        };

        return depthStencil;
    }
}
