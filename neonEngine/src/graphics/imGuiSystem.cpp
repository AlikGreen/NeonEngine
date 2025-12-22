#include "imGuiSystem.h"

#include "graphicsSystem.h"
#include "renderSystem.h"
#include "components/camera.h"
#include "core/sceneManager.h"
#include "events/rhiWindowEvent.h"
#include "imgui/imGuiExtensions.h"
#include "windows/consoleWindow.h"
#include "windows/statsWindow.h"
#include "windows/viewportWindow.h"

namespace Neon
{

    void setNeonImGuiStyle()
    {
        ImGuiStyle &style = ImGui::GetStyle();
        NeonGui::LoadStyle(AssetManager::getFullPath("style.yaml"), style);
    }

    void ImGuiSystem::preStartup()
    {
        m_graphicsSystem = Engine::getSystem<GraphicsSystem>();
        m_device = m_graphicsSystem->getDevice();
        m_window = m_graphicsSystem->getWindow();

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();

        io.Fonts->Clear();

        io.FontDefault = io.Fonts->AddFontFromFileTTF(AssetManager::getFullPath(R"(fonts\JetBrainsMono-Regular.ttf)").c_str(), 22.0f);

        ImFontConfig mergeCfg{};
        mergeCfg.MergeMode = true;
        mergeCfg.PixelSnapH = true;

        // Include the full BMP (0x0020..0xFFFF) so all symbols from the font get baked.
        // (Noto Sans Symbols 2 glyphs are in BMP; this captures them.)
        static constexpr ImWchar rangesAllBMP[] =
        {
            0x0020, 0xFFFF,
            0
        };

        io.Fonts->AddFontFromFileTTF(
            AssetManager::getFullPath(R"(fonts\NotoSansSymbols2-Regular.ttf)").c_str(),
            22.0f,              // same size as base for consistent alignment
            &mergeCfg,
            rangesAllBMP
        );

        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // optional
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;


        const RHI::TextureDescription colDesc = RHI::TextureDescription::Texture2D(
                m_window->getWidth(),
                m_window->getHeight(),
                RHI::PixelFormat::R8G8B8A8Unorm,
                RHI::TextureUsage::ColorTarget);

        const Rc<RHI::Texture> colTex = m_device->createTexture(colDesc);

        const RHI::TextureViewDescription viewDesc(colTex);
        m_colorTextureView = m_device->createTextureView(viewDesc);

        RHI::FramebufferDescription framebufferDesc{};
        framebufferDesc.colorTargets.push_back(m_colorTextureView);

        const Rc<RHI::Framebuffer> framebuffer = m_device->createFramebuffer(framebufferDesc);

        RHI::SamplerDescription samplerDesc{};
        samplerDesc.wrapMode.x = RHI::TextureWrap::ClampToEdge;
        samplerDesc.wrapMode.y = RHI::TextureWrap::ClampToEdge;
        m_colorTextureSampler = m_device->createSampler(samplerDesc);

        RHI::ImGuiController::InitInfo initInfo{};
        initInfo.device      = m_device;
        initInfo.framebuffer = framebuffer;
        initInfo.window      = m_window;

        m_imGuiController = makeBox<RHI::ImGuiController>(initInfo);

        m_frameCountStart = std::chrono::high_resolution_clock::now();

        setNeonImGuiStyle();

        m_windows.push_back(makeRc<StatsWindow>());
        m_windows.push_back(makeRc<ViewportWindow>());
        m_windows.push_back(makeRc<ConsoleWindow>());
    }

    void ImGuiSystem::update()
    {
        m_frameCount++;

        const std::chrono::time_point<std::chrono::high_resolution_clock> end = std::chrono::high_resolution_clock::now();

        if(end - m_frameCountStart >= std::chrono::seconds(1))
        {
            m_fps = m_frameCount;
            m_frameTime = static_cast<float>((1.0 / static_cast<double>(m_fps)) * 1000.0);
            m_frameCountStart = end;
            m_frameCount = 0;
        }
    }

    void ImGuiSystem::render()
    {
        ImGuiIO &io = ImGui::GetIO();
        io.DisplaySize = ImVec2(
            static_cast<float>(m_window->getWidth()),
            static_cast<float>(m_window->getHeight())
        );
        io.DeltaTime = Engine::getDeltaTime();

        m_imGuiController->newFrame();

        drawDockSpace();

        for(const auto& window : m_windows)
        {
            if(!window->open) continue;
            ImGui::Begin(window->getName().c_str(), &window->open);

            window->render();

            ImGui::End();
        }

        ImGui::ShowDemoWindow();

        m_imGuiController->endFrame();

        m_graphicsSystem->drawTexture(m_colorTextureView, m_colorTextureSampler);
    }

    void ImGuiSystem::drawDockSpace()
    {
        ImGuiIO &io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

        ImGuiDockNodeFlags dockspaceFlags = 0;
        dockspaceFlags |= ImGuiDockNodeFlags_PassthruCentralNode;

        const ImGuiViewport *viewport = ImGui::GetMainViewport();

        // Make host window + dockspace background transparent
        ImGui::PushStyleColor(ImGuiCol_WindowBg,      ImVec4(0, 0, 0, 0));
        ImGui::PushStyleColor(ImGuiCol_DockingEmptyBg,ImVec4(0, 0, 0, 0));

        // dockspace_id = 0 → ImGui will generate one
        ImGui::DockSpaceOverViewport(
            0,
            viewport,
            dockspaceFlags
        );

        ImGui::PopStyleColor(2);

    }

    void ImGuiSystem::event(Event *event)
    {
        if(const auto* rhiWindowEvent = dynamic_cast<RhiWindowEvent*>(event))
        {
            RHI::ImGuiController::processEvent(rhiWindowEvent->event);
        }
    }
}
