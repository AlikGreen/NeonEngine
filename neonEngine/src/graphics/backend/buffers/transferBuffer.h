#pragma once

#include <vector>
#include <stdexcept>
#include <algorithm>

#include "../physicalDevice.h"

namespace Neon
{
    class TransferBuffer
    {
    public:
        explicit TransferBuffer(size_t size, SDL_GPUTransferBufferUsage usage = SDL_GPU_TRANSFERBUFFERUSAGE_UPLOAD);
        ~TransferBuffer();

        // No copy constructor or assignment
        TransferBuffer(const TransferBuffer&) = delete;
        TransferBuffer& operator=(const TransferBuffer&) = delete;

        // Move constructor and assignment
        TransferBuffer(TransferBuffer&& other) noexcept;

        TransferBuffer& operator=(TransferBuffer&& other) noexcept;

        template<typename T>
        T* map(bool readOnly = false)
        {
            if (mapped) {
                throw std::runtime_error("Transfer buffer is already mapped");
            }

            void* data = SDL_MapGPUTransferBuffer(*device, transferBuffer, readOnly);
            mapped = true;
            return static_cast<T*>(data);
        }

        void unmap();

        template<typename T>
        void uploadData(SDL_GPUBuffer* destBuffer, const std::vector<T>& data, const size_t destOffset = 0)
        {
            if (data.size() * sizeof(T) > size) {
                throw std::runtime_error("Data size exceeds transfer buffer size");
            }

            // Map and copy data
            T* mappedData = map<T>(false);
            std::ranges::copy(data.begin(), data.end(), mappedData);
            unmap();

            // Create command buffer and submit copy command
            SDL_GPUCommandBuffer* commandBuffer = SDL_AcquireGPUCommandBuffer(*device);
            if (!commandBuffer) {
                throw std::runtime_error("Failed to acquire command buffer");
            }

            SDL_GPUCopyPass* copyPass = SDL_BeginGPUCopyPass(commandBuffer);

            SDL_GPUTransferBufferLocation transferBufferLocation{};
            transferBufferLocation.transfer_buffer = transferBuffer;
            transferBufferLocation.offset = 0;

            SDL_GPUBufferRegion bufferRegion{};
            bufferRegion.buffer = destBuffer;
            bufferRegion.offset = destOffset;
            bufferRegion.size = data.size() * sizeof(T);

            SDL_UploadToGPUBuffer(copyPass, &transferBufferLocation, &bufferRegion, false);
            SDL_EndGPUCopyPass(copyPass);

            if (!SDL_SubmitGPUCommandBuffer(commandBuffer))
                {
                throw std::runtime_error("Failed to submit command buffer");
            }
        }

        [[nodiscard]] SDL_GPUTransferBuffer* getHandle() const
        {
            return transferBuffer;
        }

        [[nodiscard]] size_t getSize() const
        {
            return size;
        }

    private:
        const PhysicalDevice* device;
        SDL_GPUTransferBuffer* transferBuffer;
        size_t size;
        bool mapped;
    };
}
