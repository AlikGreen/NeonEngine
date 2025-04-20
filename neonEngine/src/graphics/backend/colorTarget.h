#pragma once
#include <SDL3/SDL.h>

#include "texture.h"
#include "glm/vec4.hpp"

namespace Neon
{
enum class StoreOperation
{
    Store, DontCare, Resolve, ResolveAndStore
};

enum class LoadOperation
{
    Clear, Load, DontCare
};

class ColorTarget
{
public:
    ColorTarget(Texture texture);

    operator SDL_GPUColorTargetInfo() const;

    LoadOperation loadOperation = LoadOperation::Clear;
    StoreOperation storeOperation = StoreOperation::Store;
    glm::vec4 clearColor = glm::vec4(1, 1, 1, 1);
    Texture texture;
private:
    static SDL_GPUStoreOp storeOpToSDL(StoreOperation storeOp);
    static SDL_GPULoadOp loadOpToSDL(LoadOperation loadOp);
};
}
