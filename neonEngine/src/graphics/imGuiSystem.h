#pragma once
#include <chrono>

#include "imgui/imGuiController.h"
#include "core/system.h"

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
    RHI::Device* m_device{};
    RHI::Window* m_window{};

    size_t m_fps = 0;
    float m_frameTime = 0;
    size_t m_frameCount = 0;
    std::chrono::time_point<std::chrono::high_resolution_clock> m_frameCountStart;
};
}
