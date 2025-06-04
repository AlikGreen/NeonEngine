#pragma once
#include "graphics/api/buffers/vertexBuffer.h"
#include <glad/glad.h>

namespace Neon
{
class VertexBufferOGL : public VertexBuffer
{
public:
    VertexBufferOGL();
    VertexBufferOGL(void* data, uint32_t elementCount, uint32_t elementSize);

    [[nodiscard]] uint32_t getStride() const;

    void bind() const;
    void uploadData(const void* data, uint32_t size) const;
protected:
    void uploadDataImpl(void* data, uint32_t elementCount, uint32_t elementSize) override;
private:
    GLuint handle{};
    uint32_t elementSize{};
    uint32_t elementCount{};
};
}
