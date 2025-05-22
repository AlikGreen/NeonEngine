#pragma once
#include <stdexcept>
#include <vector>
#include <SDL3/SDL_gpu.h>

#include "../physicalDevice.h"
#include <iostream>

#include "transferBuffer.h"
#include "../../renderSystem.h"
#include "core/engine.h"


namespace Neon
{
    template<typename T>
    class VertexBuffer
    {
    public:
        explicit VertexBuffer(const uint32_t size)
        {
            const auto* renderSystem = Engine::getSystem<RenderSystem>();
            const PhysicalDevice* device = renderSystem->getDevice();
            SDL_GPUBufferCreateInfo vertexBufferDesc{};
            vertexBufferDesc.size = size*sizeof(T);
            vertexBufferDesc.usage = SDL_GPU_BUFFERUSAGE_VERTEX;

            handle = SDL_CreateGPUBuffer(*device, &vertexBufferDesc);
            if(!handle)
                throw std::runtime_error("Failed to create vertex buffer");
        }

        explicit VertexBuffer(std::vector<T> data)
        {
            const auto* renderSystem = Engine::getSystem<RenderSystem>();
            const PhysicalDevice* device = renderSystem->getDevice();
            SDL_GPUBufferCreateInfo vertexBufferDesc{};
            vertexBufferDesc.size = data.size()*sizeof(T);
            vertexBufferDesc.usage = SDL_GPU_BUFFERUSAGE_VERTEX;

            handle = SDL_CreateGPUBuffer(*device, &vertexBufferDesc);
            if(!handle)
                throw std::runtime_error("Failed to create vertex buffer");

            uploadData(data);
        }


        void uploadData(std::vector<T> data)
        {
            TransferBuffer transferBuffer(data.size() * sizeof(T));
            transferBuffer.uploadData<T>(handle, data);
        }

        operator SDL_GPUBuffer*() const
        {
            return handle;
        }

        [[nodiscard]] SDL_GPUBuffer* getHandle() const
        {
            return handle;
        }
    private:
        SDL_GPUBuffer* handle;
    };
}
