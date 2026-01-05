#pragma once
#include "device.h"
#include "textureView.h"

namespace Neon
{
class RenderTarget
{
public:
    void resize(uint32_t w, uint32_t h);

    Rc<RHI::TextureView> getColorAttachment() { return m_colorAttachment; }
    Rc<RHI::TextureView> getDepthAttachment() { return m_depthAttachment; }
    [[nodiscard]] uint32_t getWidth() const { return m_width; }
    [[nodiscard]] uint32_t getHeight() const { return m_height; }
private:
    friend class GraphicsSystem;
    RenderTarget(const Rc<RHI::Device> &device, uint32_t w, uint32_t h, bool useDepth);

    Rc<RHI::Device> m_device;

    Rc<RHI::TextureView> m_colorAttachment;
    Rc<RHI::TextureView> m_depthAttachment;

    bool m_useDepth;
    uint32_t m_width{};
    uint32_t m_height{};
};
}
