#include "physicalDevice.h"

#include <iostream>
#include <ostream>
#include <stdexcept>

namespace Neon
{
    PhysicalDevice::PhysicalDevice(Window* window)
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

    SDL_GPUDevice * PhysicalDevice::getHandle() const
    {
        return handle;
    }
}
