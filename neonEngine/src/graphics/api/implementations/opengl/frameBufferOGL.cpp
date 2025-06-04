#include "frameBufferOGL.h"

namespace Neon
{
    FrameBufferOGL::FrameBufferOGL(const GLuint existing) : handle(existing)
    {
    }

    void FrameBufferOGL::bind() const
    {
        glBindFramebuffer(GL_FRAMEBUFFER, handle);
    }
}
