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
        targetInfo.store_op = storeOpToSDL(storeOperation);
        targetInfo.load_op = loadOpToSDL(loadOperation);
        targetInfo.clear_color = {clearColor.r, clearColor.g, clearColor.b, clearColor.a};

        return targetInfo;
    }

    SDL_GPUStoreOp ColorTarget::storeOpToSDL(const StoreOperation storeOp)
    {
        switch (storeOp)
        {
            case StoreOperation::Store:
                return SDL_GPU_STOREOP_STORE;
            case StoreOperation::Resolve:
                return SDL_GPU_STOREOP_RESOLVE;
            case StoreOperation::DontCare:
                return SDL_GPU_STOREOP_DONT_CARE;
            case StoreOperation::ResolveAndStore:
                return SDL_GPU_STOREOP_RESOLVE_AND_STORE;
        }
        return SDL_GPU_STOREOP_DONT_CARE;
    }

    SDL_GPULoadOp ColorTarget::loadOpToSDL(const LoadOperation loadOp)
    {
        switch (loadOp)
        {
            case LoadOperation::Clear:
                return SDL_GPU_LOADOP_CLEAR;
            case LoadOperation::Load:
                return SDL_GPU_LOADOP_LOAD;
            case LoadOperation::DontCare:
                return SDL_GPU_LOADOP_DONT_CARE;
        }

        return SDL_GPU_LOADOP_DONT_CARE;
    }
}
