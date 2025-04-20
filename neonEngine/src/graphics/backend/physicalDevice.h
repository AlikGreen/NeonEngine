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
        explicit PhysicalDevice(Window* window);

        operator SDL_GPUDevice*() const;
        [[nodiscard]] SDL_GPUDevice* getHandle() const;
        [[nodiscard]] BackendAPI getBackendApi() const;

        [[nodiscard]] CommandBuffer acquireCommandBuffer() const;
    private:
        SDL_GPUDevice *handle;
        BackendAPI backendAPI;
    };
}
