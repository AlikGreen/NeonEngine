#pragma once
#include <cstdint>
#include <vector>
#include "buffer.h"

namespace Neon
{
class VertexBuffer : public Buffer
{
public:
    ~VertexBuffer() override = default;

    template<typename T>
    void uploadData(const std::vector<T> data)
    {
        uploadDataImpl(data.data(), data.size(), sizeof(T));
    }
protected:
    virtual void uploadDataImpl(void* data, uint32_t elementCount, uint32_t elementSize) = 0;
};
}
