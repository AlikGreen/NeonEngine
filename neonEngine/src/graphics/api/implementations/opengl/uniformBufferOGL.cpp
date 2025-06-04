#include "uniformBufferOGL.h"

namespace Neon
{
    UniformBufferOGL::UniformBufferOGL()
    {
        glGenBuffers(1, &handle);
    }

    UniformBufferOGL::UniformBufferOGL(const void *data, const uint32_t size) : size(size)
    {
        glGenBuffers(1, &handle);
        bind();
        glBufferData(GL_UNIFORM_BUFFER, size, data, GL_DYNAMIC_DRAW);
        unbind();
    }

    void UniformBufferOGL::uploadData(const void *data, const uint32_t size)
    {
        bind();
        if(size > this->size)
        {
            glBufferData(GL_UNIFORM_BUFFER, size, data, GL_DYNAMIC_DRAW);
            this->size = size;
        }
        else
            glBufferSubData(GL_UNIFORM_BUFFER, 0, size, data);

        GLenum error = glGetError();
        if (error != GL_NO_ERROR) {
            printf("OpenGL error in uploadData: %d\n", error);
        }
        glMemoryBarrier(GL_UNIFORM_BARRIER_BIT);
        unbind();
    }

    void UniformBufferOGL::bind() const
    {
        glBindBuffer(GL_UNIFORM_BUFFER, handle);
    }

    void UniformBufferOGL::unbind() const
    {
        glBindBuffer(GL_UNIFORM_BUFFER, 0);
    }

    void UniformBufferOGL::bindBase(const uint32_t index) const
    {
        glBindBufferBase(GL_UNIFORM_BUFFER, index, handle);
    }
}
