#pragma once
#include "glad/glad.h"
#include "../../buffers/uniformBuffer.h"

namespace Neon
{
class UniformBufferOGL : public UniformBuffer
{
public:
    UniformBufferOGL();
    UniformBufferOGL(const void *data, uint32_t size);
    void uploadData(const void *data, uint32_t size);

    void bind() const;
    void unbind() const;
    void bindBase(uint32_t index) const;
private:
    GLuint handle{};
    uint32_t size = 0;
};
}
