#pragma once
#include "graphics/api/buffers/vertexBuffer.h"
#include "util/memory.h"

namespace Neon
{
struct VertexBufferBinding
{
    Ref<VertexBuffer> vertexBuffer{};
    int offset{};
};
}
