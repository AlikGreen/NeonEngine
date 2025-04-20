#include "renderSystem.h"


#include "../neonEngine.h"
#include "backend/colorTarget.h"
#include "backend/commandBuffer.h"
#include "backend/shader.h"
#include "backend/texture.h"
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
	    const CommandBuffer commandBuffer = physicalDevice->acquireCommandBuffer();

	    const Texture swapChainTexture = commandBuffer.waitForSwapChainTexture();

    	auto colorTarget = ColorTarget(swapChainTexture);
    	colorTarget.clearColor = {0.0f, 0.6f, 0.0f ,1.0f};

        RenderPass renderPass = commandBuffer.beginRenderPass({colorTarget});
    	renderPass.bindPipeline(pipeline);

        const std::vector<SDL_GPUBufferBinding> bufferBindings =
    	{
    		{ *vertexBuffer, 0 }
    	};

    	renderPass.bindVertexBuffers(0, bufferBindings);
    	renderPass.draw(3, 1);

        renderPass.end();

        commandBuffer.submit();

    	window->pollEvents();
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
