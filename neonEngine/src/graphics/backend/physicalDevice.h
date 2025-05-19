#pragma once
#include "backendAPIEnum.h"
#include "commandBuffer.h"
#include "window.h"
#include "SDL3/SDL.h"

namespace Neon
{
    class PhysicalDevice
    {
    public:
        explicit PhysicalDevice(const Window* window);

        operator SDL_GPUDevice*() const;
        [[nodiscard]] SDL_GPUDevice* getHandle() const;
        [[nodiscard]] BackendAPI getBackendApi() const;

        [[nodiscard]] CommandBuffer acquireCommandBuffer() const;
        [[nodiscard]] TextureFormat getSwapchainTextureFormat() const;
    private:
        SDL_GPUDevice *handle;
        BackendAPI backendAPI;
    };
}
