#pragma once
#include <vector>
#include <SDL3/SDL.h>

#include "physicalDevice.h"
#include "renderPass.h"

namespace Neon
{
    class CommandBuffer
    {
    public:
        CommandBuffer();

        void submit() const;

        [[nodiscard]] SDL_GPUTexture* waitForSwapChainTexture() const;
        [[nodiscard]] RenderPass beginRenderPass(const std::vector<SDL_GPUColorTargetInfo> &colorTargets) const;

        operator SDL_GPUCommandBuffer*() const;
        [[nodiscard]] SDL_GPUCommandBuffer* getHandle() const;
    private:
        PhysicalDevice* device;
        Window* window;
        SDL_GPUCommandBuffer* handle;
    };
}
