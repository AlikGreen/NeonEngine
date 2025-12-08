#include "imGuiSystem.h"

#include "renderSystem.h"
#include "input/events/keyDownEvent.h"
#include "input/events/keyUpEvent.h"
#include "input/events/mouseButtonDownEvent.h"
#include "input/events/mouseButtonUpEvent.h"
#include "input/events/mouseMoveEvent.h"

namespace Neon
{

    void setNeonImGuiStyle()
    {
        ImGuiStyle &style = ImGui::GetStyle();
        ImVec4 *colors = style.Colors;

        style.WindowPadding     = ImVec2(10.0f, 10.0f);
        style.FramePadding      = ImVec2(8.0f, 4.0f);
        style.ItemSpacing       = ImVec2(8.0f, 6.0f);
        style.ItemInnerSpacing  = ImVec2(6.0f, 4.0f);
        style.ScrollbarSize     = 14.0f;
        style.GrabMinSize       = 10.0f;

        style.WindowRounding    = 8.0f;
        style.ChildRounding     = 8.0f;
        style.FrameRounding     = 6.0f;
        style.ScrollbarRounding = 8.0f;
        style.GrabRounding      = 6.0f;
        style.TabRounding       = 6.0f;

        style.WindowBorderSize  = 1.0f;
        style.FrameBorderSize   = 1.0f;
        style.TabBorderSize     = 0.0f;

        style.WindowTitleAlign  = ImVec2(0.0f, 0.5f);
        style.ColorButtonPosition = ImGuiDir_Right;

        style.SeparatorTextBorderSize = 1.0f;
        style.SeparatorTextPadding    = ImVec2(12.0f, 6.0f);
        style.SeparatorTextAlign      = ImVec2(0.0f, 0.5f);

        ImGui::GetIO().ConfigWindowsMoveFromTitleBarOnly = true;

        ImVec4 bg         = ImVec4(0.08f, 0.09f, 0.11f, 1.0f);
        ImVec4 bgAlt      = ImVec4(0.11f, 0.12f, 0.15f, 1.0f);
        ImVec4 bgHover    = ImVec4(0.16f, 0.18f, 0.22f, 1.0f);
        ImVec4 bgActive   = ImVec4(0.23f, 0.26f, 0.31f, 1.0f);
        ImVec4 accent     = ImVec4(0.23f, 0.63f, 0.98f, 1.0f);
        ImVec4 accentDim  = ImVec4(0.19f, 0.46f, 0.78f, 1.0f);
        ImVec4 accentSoft = ImVec4(0.19f, 0.46f, 0.78f, 0.35f);
        ImVec4 text       = ImVec4(0.92f, 0.94f, 0.96f, 1.0f);
        ImVec4 textDim    = ImVec4(0.66f, 0.70f, 0.76f, 1.0f);

        colors[ImGuiCol_Text]                  = text;
        colors[ImGuiCol_TextDisabled]          = textDim;

        colors[ImGuiCol_WindowBg]              = bg;
        colors[ImGuiCol_ChildBg]               = ImVec4(0, 0, 0, 0);
        colors[ImGuiCol_PopupBg]               = ImVec4(0.10f, 0.11f, 0.14f, 0.98f);

        colors[ImGuiCol_Border]                = ImVec4(0.16f, 0.17f, 0.22f, 1.0f);
        colors[ImGuiCol_BorderShadow]          = ImVec4(0, 0, 0, 0);

        colors[ImGuiCol_FrameBg]               = bgAlt;
        colors[ImGuiCol_FrameBgHovered]        = bgHover;
        colors[ImGuiCol_FrameBgActive]         = bgActive;

        colors[ImGuiCol_TitleBg]               = bg;
        colors[ImGuiCol_TitleBgActive]         = bgAlt;
        colors[ImGuiCol_TitleBgCollapsed]      = ImVec4(0.06f, 0.06f, 0.07f, 0.80f);

        colors[ImGuiCol_MenuBarBg]             = bgAlt;

        colors[ImGuiCol_ScrollbarBg]           = bg;
        colors[ImGuiCol_ScrollbarGrab]         = ImVec4(0.22f, 0.24f, 0.29f, 1.0f);
        colors[ImGuiCol_ScrollbarGrabHovered]  = ImVec4(0.30f, 0.33f, 0.40f, 1.0f);
        colors[ImGuiCol_ScrollbarGrabActive]   = ImVec4(0.37f, 0.40f, 0.48f, 1.0f);

        colors[ImGuiCol_CheckMark]             = accent;

        colors[ImGuiCol_SliderGrab]            = accentDim;
        colors[ImGuiCol_SliderGrabActive]      = accent;

        colors[ImGuiCol_Button]                = bgAlt;
        colors[ImGuiCol_ButtonHovered]         = bgHover;
        colors[ImGuiCol_ButtonActive]          = bgActive;

        colors[ImGuiCol_Header]                = accentSoft;
        colors[ImGuiCol_HeaderHovered]         = ImVec4(accent.x, accent.y, accent.z, 0.65f);
        colors[ImGuiCol_HeaderActive]          = accent;

        colors[ImGuiCol_Separator]             = ImVec4(0.24f, 0.26f, 0.31f, 1.0f);
        colors[ImGuiCol_SeparatorHovered]      = accentDim;
        colors[ImGuiCol_SeparatorActive]       = accent;

        colors[ImGuiCol_ResizeGrip]            = ImVec4(0.31f, 0.32f, 0.38f, 0.50f);
        colors[ImGuiCol_ResizeGripHovered]     = accentDim;
        colors[ImGuiCol_ResizeGripActive]      = accent;

        colors[ImGuiCol_Tab]                   = ImVec4(0.14f, 0.15f, 0.19f, 1.0f);
        colors[ImGuiCol_TabHovered]            = ImVec4(0.22f, 0.23f, 0.28f, 1.0f);
        colors[ImGuiCol_TabActive]             = ImVec4(0.18f, 0.19f, 0.24f, 1.0f);
        colors[ImGuiCol_TabUnfocused]          = ImVec4(0.10f, 0.10f, 0.13f, 1.0f);
        colors[ImGuiCol_TabUnfocusedActive]    = ImVec4(0.15f, 0.16f, 0.20f, 1.0f);

        colors[ImGuiCol_DockingEmptyBg]        = ImVec4(0.04f, 0.04f, 0.06f, 1.0f);

        colors[ImGuiCol_TableHeaderBg]         = ImVec4(0.15f, 0.16f, 0.20f, 1.0f);
        colors[ImGuiCol_TableBorderStrong]     = ImVec4(0.18f, 0.19f, 0.24f, 1.0f);
        colors[ImGuiCol_TableBorderLight]      = ImVec4(0.12f, 0.13f, 0.17f, 1.0f);
        colors[ImGuiCol_TableRowBg]            = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
        colors[ImGuiCol_TableRowBgAlt]         = ImVec4(1.0f, 1.0f, 1.0f, 0.03f);

        colors[ImGuiCol_TextSelectedBg]        = ImVec4(accent.x, accent.y, accent.z, 0.35f);

        colors[ImGuiCol_DragDropTarget]        = accent;

        colors[ImGuiCol_NavHighlight]          = accentSoft;
        colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.0f, 1.0f, 1.0f, 0.70f);
        colors[ImGuiCol_NavWindowingDimBg]     = ImVec4(0.0f, 0.0f, 0.0f, 0.30f);
        colors[ImGuiCol_ModalWindowDimBg]      = ImVec4(0.0f, 0.0f, 0.0f, 0.45f);
    }


    void ImGuiSystem::preStartup()
    {
        const auto renderSys = Engine::getSystem<RenderSystem>();
        m_device = renderSys->getDevice();
        m_window = renderSys->getWindow();

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();

        io.Fonts->Clear();
        io.FontDefault = nullptr;

        // Minimal, known-good font:
        io.Fonts->AddFontDefault();

        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // optional
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

        RHI::ImGuiController::InitInfo initInfo{};
        initInfo.device      = m_device;
        initInfo.framebuffer = m_device->getSwapChainFramebuffer();
        initInfo.window      = m_window;

        m_imGuiController = makeBox<RHI::ImGuiController>(initInfo);

        m_frameCountStart = std::chrono::high_resolution_clock::now();

        setNeonImGuiStyle();
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

        ImGui::ShowDemoWindow();


        ImGui::Begin("Statistics");
        ImGui::Text("FPS: %d", m_fps);
        ImGui::Text("Frame Time: %.4f ms", m_frameTime);
        ImGui::End();

        m_imGuiController->endFrame();
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

        // This uses an implicit host window over 'viewport'
        // dockspace_id = 0 → ImGui will generate one
        ImGui::DockSpaceOverViewport(
            0,                  // dockspace_id
            viewport,           // viewport
            dockspaceFlags     // flags
        );

        ImGui::PopStyleColor(2);
    }


    void ImGuiSystem::event(Event *event)
    {
        if(const auto* mouseMoveEvent = dynamic_cast<MouseMoveEvent*>(event))
        {
            RHI::Event e{};
            e.type = RHI::Event::Type::MouseMotion;
            e.motion.x = mouseMoveEvent->getX();
            e.motion.y = mouseMoveEvent->getY();

            RHI::ImGuiController::processEvent(e);
        }
        if(const auto* mouseDownEvent = dynamic_cast<MouseButtonDownEvent*>(event))
        {
            RHI::Event e{};
            e.type = RHI::Event::Type::MouseButtonDown;
            e.button.button = mouseDownEvent->getButton();

            RHI::ImGuiController::processEvent(e);
        }
        if(const auto* mouseUpEvent = dynamic_cast<MouseButtonUpEvent*>(event))
        {
            RHI::Event e{};
            e.type = RHI::Event::Type::MouseButtonUp;
            e.button.button = mouseUpEvent->getButton();

            RHI::ImGuiController::processEvent(e);
        }
        if(const auto* keyDownEvent = dynamic_cast<KeyDownEvent*>(event))
        {
            RHI::Event e{};
            e.type = RHI::Event::Type::KeyDown;
            e.key.key = keyDownEvent->getKeycode();
            e.key.repeat = keyDownEvent->isRepeat();

            RHI::ImGuiController::processEvent(e);
        }
        if(const auto* keyUpEvent = dynamic_cast<KeyUpEvent*>(event))
        {
            RHI::Event e{};
            e.type = RHI::Event::Type::KeyUp;
            e.key.key = keyUpEvent->getKeycode();
            e.key.repeat = false;

            RHI::ImGuiController::processEvent(e);
        }
    }
}
