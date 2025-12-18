#pragma once
#include <chrono>

#include "renderSystem.h"
#include "imgui/imGuiController.h"
#include "core/system.h"
#include "imgui/imGuiConfig.h"

namespace Neon
{
class ImGuiSystem final : public System
{
public:
    void preStartup() override;
    void update() override;
    void render() override;

    static void drawDockSpace();

    void event(Event *event) override;
private:
    Box<RHI::ImGuiController> m_imGuiController;
    Rc<RHI::Device> m_device{};
    Rc<RHI::Window> m_window{};

    Rc<RHI::TextureView> m_colorTextureView{};
    Rc<RHI::Sampler> m_colorTextureSampler{};

    GraphicsSystem* m_graphicsSystem{};

    Box<RHI::ImGuiImage> m_imguiImage{};

    size_t m_fps = 0;
    float m_frameTime = 0;
    size_t m_frameCount = 0;
    std::chrono::time_point<std::chrono::high_resolution_clock> m_frameCountStart;
};
}
