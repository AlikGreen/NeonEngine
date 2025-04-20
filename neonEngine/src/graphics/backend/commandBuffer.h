#pragma once
#include <vector>
#include <SDL3/SDL.h>

#include "colorTarget.h"
#include "renderPass.h"
#include "texture.h"

namespace Neon
{
    class Window;
    class PhysicalDevice;

    class CommandBuffer
    {
    public:
        void submit() const;

        [[nodiscard]] Texture waitForSwapChainTexture() const;
        [[nodiscard]] RenderPass beginRenderPass(const std::vector<ColorTarget> &colorTargets) const;

        operator SDL_GPUCommandBuffer*() const;
        [[nodiscard]] SDL_GPUCommandBuffer* getHandle() const;
    private:
        friend class PhysicalDevice;
        explicit CommandBuffer(SDL_GPUCommandBuffer* handle);

        PhysicalDevice* device;
        Window* window;
        SDL_GPUCommandBuffer* handle;
    };
}
