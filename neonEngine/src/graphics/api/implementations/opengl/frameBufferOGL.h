#pragma once
#include "commandListOGL.h"
#include "graphics/api/frameBuffer.h"

namespace Neon
{
class FrameBufferOGL final : public FrameBuffer
{
public:
    explicit FrameBufferOGL(GLuint existing);

    void bind() const;
private:
    GLuint handle;
};
}
