#pragma once
#include <SDL3/SDL_gpu.h>

#include "convertSDL.h"
#include "texture.h"

namespace Neon
{
class DepthStencilTarget
{
public:
    explicit DepthStencilTarget(Texture texture);

    operator SDL_GPUDepthStencilTargetInfo() const;

    LoadOperation loadOperation = LoadOperation::Clear;
    StoreOperation storeOperation = StoreOperation::Store;
    float clearDepth = 1.0f;
    Texture texture;
};
}
