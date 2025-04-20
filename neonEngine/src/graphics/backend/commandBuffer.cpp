#include "commandBuffer.h"

#include "colorTarget.h"
#include "renderPass.h"
#include "texture.h"
#include "../renderSystem.h"
#include "../../neonEngine.h"

namespace Neon
{
    CommandBuffer::CommandBuffer(SDL_GPUCommandBuffer *handle) : handle(handle)
    {
        const RenderSystem* renderSystem = Engine::getInstance()->getSystem<RenderSystem>();
        device = renderSystem->getDevice();
        window = renderSystem->getWindow();
    }

    void CommandBuffer::submit() const
    {
        if(!SDL_SubmitGPUCommandBuffer(handle))
            throw std::runtime_error("Failed to submit command buffer to GPU");
    }

    Texture CommandBuffer::waitForSwapChainTexture() const
    {
        SDL_GPUTexture* swapChainTexture;
        SDL_WaitAndAcquireGPUSwapchainTexture(handle, *window, &swapChainTexture, nullptr, nullptr);
        if(!swapChainTexture)
            throw std::runtime_error("Failed to acquire swap chain texture");
        return Texture(swapChainTexture);
    }

    RenderPass CommandBuffer::beginRenderPass(const std::vector<ColorTarget> &colorTargets) const
    {
        std::vector<SDL_GPUColorTargetInfo> sdlColorTargets;
        sdlColorTargets.reserve(colorTargets.size());

        for (auto& target : colorTargets)
        {
            sdlColorTargets.push_back(target);
        }


        return RenderPass(SDL_BeginGPURenderPass(handle, sdlColorTargets.data(), sdlColorTargets.size(), nullptr));
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
