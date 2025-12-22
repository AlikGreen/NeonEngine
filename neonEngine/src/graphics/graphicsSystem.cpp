#include "graphicsSystem.h"

#include "window.h"
#include "core/engine.h"
#include "core/eventManager.h"
#include "events/dropFileEvent.h"
#include "events/quitEvent.h"
#include "events/rhiWindowEvent.h"
#include "events/windowResizeEvent.h"
#include "implementations/opengl/blitShader.h"
#include "input/events/keyDownEvent.h"
#include "input/events/keyUpEvent.h"
#include "input/events/mouseButtonDownEvent.h"
#include "input/events/mouseButtonUpEvent.h"
#include "input/events/mouseMoveEvent.h"
#include "input/events/mouseWheelEvent.h"
#include "input/events/textInputEvent.h"

namespace Neon
{
    GraphicsSystem::GraphicsSystem(const RHI::WindowCreationOptions &windowOptions)
    {
        m_window = Box<RHI::Window>(RHI::Window::createWindow(windowOptions));
    }

    void GraphicsSystem::updateSwapchainFramebuffers()
    {
        std::vector<Rc<RHI::Texture>> textures = m_swapchain->getTextures();
        m_framebuffers.clear();

        for(const auto& texture : textures)
        {
            const RHI::TextureViewDescription viewDesc(texture);
            Rc<RHI::TextureView> colView = m_device->createTextureView(viewDesc);

            RHI::FramebufferDescription framebufferDesc{};
            framebufferDesc.colorTargets.push_back(colView);

            Rc<RHI::Framebuffer> framebuffer = m_device->createFramebuffer(framebufferDesc);
            m_framebuffers.push_back(framebuffer);
        }
    }

    void GraphicsSystem::preStartup()
    {
        m_window->run();
        m_device = m_window->createDevice();

        RHI::SwapchainDescription swapchainDesc{};
        swapchainDesc.window = m_window;
        m_swapchain = m_device->createSwapchain(swapchainDesc);

        std::vector<glm::vec2> quadPositions =
        {
            {-1, -1 },
            { 1, -1 },
            { 1,  1 },
            {-1,  1 }
        };

        std::vector<uint32_t> quadIndices =
        {
            0, 1, 2,
            0, 2, 3
        };

        Rc<RHI::Shader> shader = m_device->createShaderFromSource(RHI::blitShaderSource);
        shader->compile();

        RHI::InputLayout vertexInputState{};
        vertexInputState.addVertexBuffer<glm::vec2>(0);
        vertexInputState.addVertexAttribute<glm::vec2>(0, 0);

        RHI::DepthState depthState{};
        depthState.hasDepthTarget  = false;
        depthState.enableDepthTest = false;

        RHI::RasterizerState rasterizerState{};
        rasterizerState.cullMode = RHI::CullMode::None;

        const RHI::RenderTargetsDescription targetsDesc{};

        RHI::BlendState blendState{};
        blendState.enableBlend = true;

        RHI::GraphicsPipelineDescription pipelineDescription{};
        pipelineDescription.shader             = shader;
        pipelineDescription.inputLayout		   = vertexInputState;
        pipelineDescription.targetsDescription = targetsDesc;
        pipelineDescription.depthState         = depthState;
        pipelineDescription.rasterizerState    = rasterizerState;
        pipelineDescription.blendState         = blendState;

        m_pipeline = m_device->createPipeline(pipelineDescription);

        updateSwapchainFramebuffers();

        m_vertexBuffer = m_device->createVertexBuffer();
        m_indexBuffer = m_device->createIndexBuffer();

        Rc<RHI::CommandList> cl = m_device->createCommandList();

        cl->begin();

        cl->reserveBuffer(m_vertexBuffer, quadPositions.size() * sizeof(glm::vec2));
        cl->updateBuffer(m_vertexBuffer, quadPositions);

        cl->reserveBuffer(m_indexBuffer, quadIndices.size() * sizeof(uint32_t));
        cl->updateBuffer(m_indexBuffer, quadIndices);

        m_device->submit(cl);
    }

    void GraphicsSystem::preUpdate()
    {
        std::vector<RHI::Event> events = m_window->pollEvents();

        EventManager& eventManager = Engine::getEventManager();

        for(const auto event : events)
        {
            eventManager.queueEvent(new RhiWindowEvent(event));

            switch (event.type)
            {
                case RHI::Event::Type::Quit:
                    eventManager.queueEvent(new QuitEvent());
                break;
                case RHI::Event::Type::WindowResize:
                    eventManager.queueEvent(new WindowResizeEvent(event.window.width, event.window.height));
                    m_swapchain->resize(event.window.width, event.window.height);
                    updateSwapchainFramebuffers();
                break;
                case RHI::Event::Type::KeyDown:
                    eventManager.queueEvent(new KeyDownEvent(event.key.key, event.key.repeat));
                break;
                case RHI::Event::Type::KeyUp:
                    eventManager.queueEvent(new KeyUpEvent(event.key.key));
                break;
                case RHI::Event::Type::MouseButtonDown:
                    eventManager.queueEvent(new MouseButtonDownEvent(event.button.button));
                break;
                case RHI::Event::Type::MouseButtonUp:
                    eventManager.queueEvent(new MouseButtonUpEvent(event.button.button));
                break;
                case RHI::Event::Type::MouseMotion:
                    eventManager.queueEvent(new MouseMoveEvent(event.motion.x, event.motion.y));
                break;
                case RHI::Event::Type::MouseWheel:
                    eventManager.queueEvent(new MouseWheelEvent(event.wheel.x, event.wheel.y));
                break;
                case RHI::Event::Type::TextInput:
                    eventManager.queueEvent(new TextInputEvent(event.text.codepoint));
                break;
                case RHI::Event::Type::DropFile:
                    eventManager.queueEvent(new DropFileEvent(event.drop.path));
                break;
            }
        }
    }

    void GraphicsSystem::preRender()
    {
        m_imageIndex = m_swapchain->acquireNextImage();

        const Rc<RHI::CommandList> commandList = m_device->createCommandList();

        commandList->begin();
        commandList->setPipeline(m_pipeline);
        commandList->setFramebuffer(m_framebuffers[m_imageIndex]);
        commandList->clearColorTarget(0, {0, 0, 0, 1});
        m_device->submit(commandList);
    }

    void GraphicsSystem::postRender()
    {
        m_swapchain->present(m_imageIndex);
    }

    void GraphicsSystem::shutdown()
    {
        m_window->close();
    }

    void GraphicsSystem::drawTexture(const Rc<RHI::TextureView> &texture, const Rc<RHI::Sampler> &sampler) const
    {
        const Rc<RHI::CommandList> commandList = m_device->createCommandList();

        commandList->begin();

        commandList->setPipeline(m_pipeline);
        commandList->setFramebuffer(m_framebuffers[m_imageIndex]);

        commandList->setIndexBuffer(m_indexBuffer, RHI::IndexFormat::UInt32);
        commandList->setVertexBuffer(0, m_vertexBuffer);

        commandList->setTexture("blitTexture", texture);
        commandList->setSampler("blitTexture", sampler);

        commandList->drawIndexed(6);

        m_device->submit(commandList);
    }
}
