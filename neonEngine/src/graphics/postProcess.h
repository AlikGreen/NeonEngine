#pragma once
#include "textureView.h"

namespace Neon
{
class PostProcess
{
public:
    virtual ~PostProcess() = default;

    virtual Rc<RHI::TextureView> render(Rc<RHI::TextureView> colorTexture, Rc<RHI::TextureView> depthTexture) = 0;
};
}
