#include "imGuiSystem.h"

#include "graphicsSystem.h"
#include "renderSystem.h"
#include "components/camera.h"
#include "core/sceneManager.h"
#include "events/rhiWindowEvent.h"
#include "imgui/imGuiExtensions.h"

namespace Neon
{

    void setNeonImGuiStyle()
    {
        ImGuiStyle &style = ImGui::GetStyle();
        NeonGui::LoadStyle("style.yaml", style);
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


        io.FontDefault = io.Fonts->AddFontFromFileTTF(R"(C:\Users\alikg\Downloads\JetBrainsMono-Regular.ttf)", 22.0f);

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
        auto& world = Engine::getSceneManager().getCurrentScene().getRegistry();
        const auto cameras = world.view<Camera>();

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
        NeonGui::InputText("Text: ", input);
        NeonGui::InputInt3("Int3: ", inputSize);
        ImGui::End();

        ImGui::Begin("Viewport");

        const ImVec2 avail = ImGui::GetContentRegionAvail();

        Rc<RHI::TextureView> sceneTexture = nullptr;
        if(cameras.size() >= 1)
        {
            auto [camEntity, camera] = cameras.at(0);
            camera.setWidth(static_cast<uint32_t>(avail.x));
            camera.setHeight(static_cast<uint32_t>(avail.y));
            sceneTexture = camera.getColorTexture();
        }

        NeonGui::Image(sceneTexture, avail, ImVec2(0, 1), ImVec2(1, 0));

        ImGui::End();

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
