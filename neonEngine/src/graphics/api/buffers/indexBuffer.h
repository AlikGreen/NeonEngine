#pragma once
#include <cstdint>
#include <vector>

#include "buffer.h"

namespace Neon
{
class IndexBuffer : public Buffer
{
public:
    ~IndexBuffer() override = default;

    virtual void uploadData(std::vector<uint32_t> data) = 0;
};
}
