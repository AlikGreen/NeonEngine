#include "transferBuffer.h"

#include "../../renderSystem.h"
#include "core/engine.h"

namespace Neon
{
    TransferBuffer::TransferBuffer(const size_t size, const SDL_GPUTransferBufferUsage usage) : device(Engine::getInstance()->getSystem<RenderSystem>()->getDevice()), transferBuffer(nullptr), size(size), mapped(false)
    {
        SDL_GPUTransferBufferCreateInfo transferBufferDesc{};
        transferBufferDesc.size = size;
        transferBufferDesc.usage = usage;

        transferBuffer = SDL_CreateGPUTransferBuffer(*device, &transferBufferDesc);
        if (!transferBuffer)
        {
            throw std::runtime_error("Failed to create transfer buffer");
        }
    }

    TransferBuffer::~TransferBuffer()
    {
        if (mapped)
        {
            unmap();
        }
        if (transferBuffer)
        {
            SDL_ReleaseGPUTransferBuffer(*device, transferBuffer);
        }
    }

    TransferBuffer::TransferBuffer(TransferBuffer &&other) noexcept : device(other.device), transferBuffer(other.transferBuffer), size(other.size), mapped(other.mapped)
    {
        other.transferBuffer = nullptr;
        other.mapped = false;
    }

    TransferBuffer & TransferBuffer::operator=(TransferBuffer &&other) noexcept
    {
        if (this != &other)
        {
            if (mapped)
            {
                unmap();
            }

            if (transferBuffer)
            {
                SDL_ReleaseGPUTransferBuffer(*device, transferBuffer);
            }

            device = other.device;
            transferBuffer = other.transferBuffer;
            size = other.size;
            mapped = other.mapped;

            other.transferBuffer = nullptr;
            other.mapped = false;
        }
        return *this;
    }

    void TransferBuffer::unmap()
    {
        if (!mapped)
        {
            throw std::runtime_error("Transfer buffer is not mapped");
        }

        SDL_UnmapGPUTransferBuffer(*device, transferBuffer);
        mapped = false;
    }
}
