#include "indexBufferOGL.h"

#include <glad/glad.h>

namespace Neon
{
    IndexBufferOGL::IndexBufferOGL(const std::vector<uint32_t> &data)
    {
        glGenBuffers(1, &handle);
        uploadData(data);
    }

    void IndexBufferOGL::bind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle);
    }

    void IndexBufferOGL::uploadData(const std::vector<uint32_t> data)
    {
        bind();
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<uint32_t>(data.size()*sizeof(uint32_t)), data.data(), GL_STATIC_DRAW);
    }
}
