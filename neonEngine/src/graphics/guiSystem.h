#pragma once
#include "core/system.h"
#include "implementations/opengl/bufferOGL.h"

namespace Neon
{
class GuiSystem final : public System
{
public:
    void preStartup() override;
    void preUpdate() override;
private:
    Box<RHI::Buffer> quadVertexBuffer = nullptr;
    Box<RHI::Buffer> quadIndexBuffer = nullptr;
};
}
