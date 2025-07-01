#pragma once
#include "commandListOGL.h"
#include "graphics/api/buffer.h"

namespace Neon
{
class BufferOGL final : public Buffer
{
public:
    explicit BufferOGL(GLenum target);
    void bind() const;
    void unbind() const;
    void reserveSpace(size_t size);
    void uploadData(const void* data, size_t size) const;
    void bindBase(uint32_t binding) const;

    GLenum getTarget() const;
private:
    GLuint handle{};
    GLenum target{};
    size_t capacity{};
};
}
