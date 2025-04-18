#pragma once
#include "backendAPIEnum.h"
#include "SDL3/SDL.h"

namespace Neon
{
    class PhysicalDevice
    {
    public:
        PhysicalDevice();

        operator SDL_GPUDevice*() const;
        [[nodiscard]] SDL_GPUDevice* getHandle() const;

        [[nodiscard]] BackendAPI getBackendApi() const;
    private:
        SDL_GPUDevice *handle;
        BackendAPI backendAPI;
    };
}
