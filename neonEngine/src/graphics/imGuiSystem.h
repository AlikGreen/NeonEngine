#pragma once
#include <chrono>

#include "renderSystem.h"
#include "imgui/imGuiController.h"
#include "core/system.h"
#include "imgui/imGuiConfig.h"

namespace Neon
{
class ImGuiSystem final : public System, Log::Stream
{
public:
    ImGuiSystem();

    void preStartup() override;
    void update() override;
    void render() override;

    void addRenderCallback(const std::function<void()> &callback);

    void event(Event *event) override;

    bool shouldDrawDockSpace = false;
    bool shouldDrawConsole = false;
    bool shouldDrawStats = false;

    void handle(std::string formattedMsg, std::string rawMsg, Level level) override;

    static ImFont* headingFont;
    static ImFont* subheadingFont;
    static ImFont* regularFont;
    static ImFont* smallFont;
private:
    static void drawDockSpace();
    void drawConsole();

    std::vector<std::pair<Level, std::string>> consoleMessages{};
    std::vector<std::function<void()>> renderCallbacks{};

    Box<RHI::ImGuiController> m_imGuiController{};
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
    std::chrono::time_point<std::chrono::high_resolution_clock> m_frameCountStart{};
};
}
