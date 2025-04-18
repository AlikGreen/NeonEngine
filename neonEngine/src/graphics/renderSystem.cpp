#include "renderSystem.h"


#include "../neonEngine.h"
#include "backend/shader.h"
#include "backend/buffers/vertexBuffer.h"
#include "glm/glm.hpp"

namespace Neon
{
    RenderSystem::RenderSystem(const WindowOptions &windowOptions)
    {
    	window = new Window(windowOptions);
    }

    void RenderSystem::startup()
    {
    	window->run();
    	physicalDevice = new PhysicalDevice(window);

    	auto shader = new Shader("C:/Users/alikg/CLionProjects/neonEngine/neonEngine/resources/shaders/triangle.glsl");
    	shader->compile();

    	VertexInputState vertexInputState;
    	vertexInputState.addVertexBuffer<Vertex>(0);
    	vertexInputState.addVertexAttribute<glm::vec2>(0, 0);
    	vertexInputState.addVertexAttribute<glm::vec3>(0, 1);

    	GraphicsPipelineDescription pipelineDescription;
    	pipelineDescription.shader = shader;
    	pipelineDescription.vertexInputState = vertexInputState;
    	pipelineDescription.cullMode = CullMode::Back;


    	pipeline = new GraphicsPipeline(pipelineDescription);

    	shader->dispose();

	    const std::vector<Vertex> vertices =
    	{
    		{{-0.5, -0.5}, {1, 0, 0}},
			{{0.5, -0.5}, {0, 1, 0}},
			{{0, 0.5}, {0, 0, 1}}
    	};

    	vertexBuffer = new VertexBuffer(vertices);
    }

    void RenderSystem::render()
    {
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_EVENT_QUIT:
                    Engine::getInstance()->quit();
                default:
                    break;
            }
        }

        SDL_GPUCommandBuffer* commandBuffer = SDL_AcquireGPUCommandBuffer(*physicalDevice);
        if(!commandBuffer)
            throw std::runtime_error("Failed to acquire GPU command buffer");

        SDL_GPUTexture* swapChainTexture;
        SDL_WaitAndAcquireGPUSwapchainTexture(commandBuffer, *window, &swapChainTexture, nullptr, nullptr);
        if(!swapChainTexture)
            return;
            // throw std::runtime_error("Failed to acquire swap chain texture");

        SDL_GPUColorTargetInfo colorTarget{};
        colorTarget.texture = swapChainTexture;
        colorTarget.store_op = SDL_GPU_STOREOP_STORE;
        colorTarget.load_op = SDL_GPU_LOADOP_CLEAR;
        colorTarget.clear_color = {0, 0.6 ,0 ,1};

        const std::vector colorTargets{colorTarget};

        SDL_GPURenderPass* renderPass = SDL_BeginGPURenderPass(commandBuffer, colorTargets.data(), colorTargets.size(), nullptr);
    	SDL_BindGPUGraphicsPipeline(renderPass, *pipeline);

        const std::vector<SDL_GPUBufferBinding> bufferBindings =
    	{
    		{ *vertexBuffer, 0 }
    	};

    	SDL_BindGPUVertexBuffers(renderPass, 0, bufferBindings.data(), bufferBindings.size());
    	SDL_DrawGPUPrimitives(renderPass, 3, 1, 0, 0);

        SDL_EndGPURenderPass(renderPass);

        if(!SDL_SubmitGPUCommandBuffer(commandBuffer))
            throw std::runtime_error("Failed to submit command buffer to GPU");
    }


    PhysicalDevice* RenderSystem::getDevice() const
    {
    	return physicalDevice;
    }

    Window * RenderSystem::getWindow() const
    {
    	return window;
    }

    void RenderSystem::shutdown()
    {
        window->close();
    }
}
