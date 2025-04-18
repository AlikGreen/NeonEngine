#include "renderSystem.h"


#include "../neonEngine.h"
#include "backend/commandBuffer.h"
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

    	CommandBuffer commandBuffer;

        SDL_GPUTexture* swapChainTexture = commandBuffer.waitForSwapChainTexture();

        SDL_GPUColorTargetInfo colorTarget{};
        colorTarget.texture = swapChainTexture;
        colorTarget.store_op = SDL_GPU_STOREOP_STORE;
        colorTarget.load_op = SDL_GPU_LOADOP_CLEAR;
        colorTarget.clear_color = {0, 0.6 ,0 ,1};

        const std::vector colorTargets{colorTarget};

        RenderPass renderPass = commandBuffer.beginRenderPass(colorTargets);
    	renderPass.bindPipeline(pipeline);

        const std::vector<SDL_GPUBufferBinding> bufferBindings =
    	{
    		{ *vertexBuffer, 0 }
    	};

    	renderPass.bindVertexBuffers(0, bufferBindings);
    	renderPass.draw(3, 1);

        renderPass.end();

        commandBuffer.submit();
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
