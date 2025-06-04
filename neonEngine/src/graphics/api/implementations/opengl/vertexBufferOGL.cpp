#include "vertexBufferOGL.h"

namespace Neon
{
    VertexBufferOGL::VertexBufferOGL()
    {
        glGenBuffers(1, &handle);
    }

    VertexBufferOGL::VertexBufferOGL(void *data, const uint32_t elementCount, const uint32_t elementSize)
    {
        glGenBuffers(1, &handle);
        VertexBufferOGL::uploadDataImpl(data, elementCount, elementSize);
    }

    uint32_t VertexBufferOGL::getStride() const
    {
        return elementSize;
    }

    void VertexBufferOGL::bind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, handle);
    }

    void VertexBufferOGL::uploadData(const void *data, const uint32_t size) const
    {
        bind();
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    }

    void VertexBufferOGL::uploadDataImpl(void *data, const uint32_t elementCount, const uint32_t elementSize)
    {
        this->elementSize = elementSize;
        this->elementCount = elementCount;

        bind();
        glBufferData(GL_ARRAY_BUFFER, elementCount*elementSize, data, GL_STATIC_DRAW);
    }
}
