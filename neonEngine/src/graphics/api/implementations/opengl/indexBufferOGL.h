#pragma once
#include "commandListOGL.h"
#include "graphics/api/buffers/indexBuffer.h"

namespace Neon
{
class IndexBufferOGL final : public IndexBuffer
{
public:
    explicit IndexBufferOGL(const std::vector<uint32_t> &data);
    void bind() const;
    void uploadData(std::vector<uint32_t> data) override;
private:
    GLuint handle{};
};
}
