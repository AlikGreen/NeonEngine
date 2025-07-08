#pragma once
#include "graphics/api/texture.h"
#include "graphics/api/descriptions/textureDescription.h"

namespace Neon
{
class TextureOGL : public Texture
{
public:
    explicit TextureOGL(const TextureDescription &description);

    void bind() const;
    void unbind() const;

    uint32_t getWidth() override;
    uint32_t getHeight() override;
    uint32_t getDepth() override;

    void setData(const void* data) const;
private:
    uint32_t width{}, height{}, depth{};
    uint32_t handle{};
    TextureDescription description;
};
}
