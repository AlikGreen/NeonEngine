#pragma once
#include <chrono>

#include "renderSystem.h"
#include "imgui/imGuiController.h"
#include "core/system.h"
#include "imgui/imGuiConfig.h"
#include "windows/imGuiWindow.h"

namespace Neon
{
class ImGuiSystem final : public System
{
public:
    void preStartup() override;
    void update() override;
    void render() override;

    template<typename T, typename ...Args>
    requires std::is_base_of_v<ImGuiWindow, T>
    Rc<T> registerWindow(Args&&... args)
    {
        Rc<T> window = makeRc<T>(std::forward<Args>(args)...);
        m_windows.push_back(window);
        return window;
    }

    template<typename T>
    requires std::is_base_of_v<ImGuiWindow, T>
    [[nodiscard]] Rc<T> getWindow() const
    {
        for (const Rc<ImGuiWindow>& window : m_windows)
        {
            if (Rc<T> casted = std::dynamic_pointer_cast<T>(window))
            {
                return casted;
            }
        }
        return {};
    }

    static void drawDockSpace();

    void event(Event *event) override;
private:
    std::vector<Rc<ImGuiWindow>> m_windows;
    Box<RHI::ImGuiController> m_imGuiController;
    Rc<RHI::Device> m_device{};
    Rc<RHI::Window> m_window{};

    Rc<RHI::TextureView> m_colorTextureView{};
    Rc<RHI::Sampler> m_colorTextureSampler{};

    GraphicsSystem* m_graphicsSystem{};

    std::string input{};
    glm::ivec3 inputSize{};

    size_t m_fps = 0;
    float m_frameTime = 0;
    size_t m_frameCount = 0;
    std::chrono::time_point<std::chrono::high_resolution_clock> m_frameCountStart;
};
}
