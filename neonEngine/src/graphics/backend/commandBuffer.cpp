#include "commandBuffer.h"

#include "renderPass.h"
#include "../renderSystem.h"
#include "../../neonEngine.h"

namespace Neon
{
    CommandBuffer::CommandBuffer()
    {
        const RenderSystem* renderSystem = Engine::getInstance()->getSystem<RenderSystem>();
        device = renderSystem->getDevice();
        window = renderSystem->getWindow();
        handle = SDL_AcquireGPUCommandBuffer(*device);
        if(!handle)
            throw std::runtime_error("Failed to acquire GPU command buffer");
    }

    void CommandBuffer::submit() const
    {
        if(!SDL_SubmitGPUCommandBuffer(handle))
            throw std::runtime_error("Failed to submit command buffer to GPU");
    }

    SDL_GPUTexture * CommandBuffer::waitForSwapChainTexture() const
    {
        SDL_GPUTexture* swapChainTexture;
        SDL_WaitAndAcquireGPUSwapchainTexture(handle, *window, &swapChainTexture, nullptr, nullptr);
        if(!swapChainTexture)
            throw std::runtime_error("Failed to acquire swap chain texture");
        return swapChainTexture;
    }

    RenderPass CommandBuffer::beginRenderPass(const std::vector<SDL_GPUColorTargetInfo> &colorTargets) const
    {
        return RenderPass(SDL_BeginGPURenderPass(handle, colorTargets.data(), colorTargets.size(), nullptr));
    }

    CommandBuffer::operator SDL_GPUCommandBuffer*() const
    {
        return handle;
    }

    SDL_GPUCommandBuffer * CommandBuffer::getHandle() const
    {
        return handle;
    }
}
