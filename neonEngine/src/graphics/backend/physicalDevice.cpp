#include "physicalDevice.h"

#include <iostream>
#include <ostream>
#include <stdexcept>

#include "core/engine.h"
#include "graphics/renderSystem.h"

namespace Neon
{
    PhysicalDevice::PhysicalDevice(const Window* window)
    {
        handle = SDL_CreateGPUDevice(SDL_GPU_SHADERFORMAT_SPIRV | SDL_GPU_SHADERFORMAT_MSL | SDL_GPU_SHADERFORMAT_DXIL, true, nullptr);
        if(!handle)
            throw std::runtime_error("Failed to create GPU device");

        const auto backendAPIString = (std::string(SDL_GetGPUDeviceDriver(handle)));

        if(backendAPIString == "vulkan")
        {
            backendAPI = BackendAPI::Vulkan;
            std::cout << backendAPIString << std::endl;
        }
        else if(backendAPIString == "d3d11")
            backendAPI = BackendAPI::Directx11;
        else if(backendAPIString == "d3d12")
            backendAPI = BackendAPI::Directx12;
        else if(backendAPIString == "metal")
            backendAPI = BackendAPI::Metal;
        else
            throw std::runtime_error("Unknown backend API");

        SDL_ClaimWindowForGPUDevice(handle, *window);
    }

    PhysicalDevice::operator SDL_GPUDevice*() const
    {
        return handle;
    }

    BackendAPI PhysicalDevice::getBackendApi() const
    {
        return backendAPI;
    }

    CommandBuffer PhysicalDevice::acquireCommandBuffer() const
    {
        SDL_GPUCommandBuffer* commandBufferHandle = SDL_AcquireGPUCommandBuffer(handle);
        if(!commandBufferHandle)
            throw std::runtime_error("Failed to acquire GPU command buffer");
        return CommandBuffer(commandBufferHandle);
    }

    TextureFormat PhysicalDevice::getSwapchainTextureFormat() const
    {
        const auto* renderSystem = Engine::getSystem<RenderSystem>();
        const auto format = SDL_GetGPUSwapchainTextureFormat(handle, *renderSystem->getWindow());
        return ConvertSDL::SDLToTextureFormat(format);
    }

    SDL_GPUDevice * PhysicalDevice::getHandle() const
    {
        return handle;
    }
}
