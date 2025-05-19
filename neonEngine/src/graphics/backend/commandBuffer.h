#pragma once
#include <vector>
#include <SDL3/SDL.h>

#include "colorTarget.h"
#include "depthStencilTarget.h"
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
        [[nodiscard]] RenderPass beginRenderPass(const std::vector<ColorTarget> &colorTargets, const DepthStencilTarget* depthStencil = nullptr) const;

        template<typename T>
        void pushFragmentUniformData(T& data, const int slot) const
        {
            const size_t size = sizeof(T);
            SDL_PushGPUFragmentUniformData(
                handle,
                slot,
                &data,
                size
            );
        }

        template<typename T>
        void pushVertexUniformData(T& data, const int slot) const
        {
            const size_t size = sizeof(T);
            SDL_PushGPUVertexUniformData(
                handle,
                slot,
                &data,
                size
            );
        }

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
