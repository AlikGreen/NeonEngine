#pragma once
#include "device.h"
#include "core/system.h"
#include "descriptions/windowCreationOptions.h"

namespace Neon
{
class GraphicsSystem final : public System
{
public:
    explicit GraphicsSystem(const RHI::WindowCreationOptions &windowOptions);

    void preStartup() override;
    void preUpdate() override;
    void preRender() override;
    void postRender() override;
    void shutdown() override;

    void drawTexture(const Rc<RHI::TextureView> &texture, const Rc<RHI::Sampler> &sampler) const;

    [[nodiscard]] Rc<RHI::Device> getDevice() const { return m_device; }
    [[nodiscard]] Rc<RHI::Window> getWindow() const { return m_window; }
    [[nodiscard]] Rc<RHI::Swapchain> getSwapchain() const { return m_swapchain; }
private:
    uint32_t m_imageIndex{};

    Rc<RHI::Device> m_device;
    Rc<RHI::Window> m_window;
    Rc<RHI::Swapchain> m_swapchain{};

    Rc<RHI::Buffer> m_vertexBuffer{};
    Rc<RHI::Buffer> m_indexBuffer{};
    Rc<RHI::Pipeline> m_pipeline{};

    std::vector<Rc<RHI::Framebuffer>> m_framebuffers{};

    void updateSwapchainFramebuffers();
};
}
