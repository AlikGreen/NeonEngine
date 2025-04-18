#include "renderSystem.h"

#include <iostream>


#include "../neonEngine.h"
#include "backend/shader.h"
#include "glm/glm.hpp"

namespace Neon
{
	struct Vertex
    {
	    glm::vec2 position;
    	glm::vec3 color;
    };

    RenderSystem::RenderSystem(const WindowOptions &windowOptions)
    {
    	window = new Window(windowOptions);
    }

    void RenderSystem::startup()
    {
    	window->run();
    	physicalDevice = new PhysicalDevice();

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

    	std::vector<Vertex> vertices =
    	{
    		{{-0.5, -0.5}, {1, 0, 0}},
			{{0.5, -0.5}, {0, 1, 0}},
			{{0, 0.5}, {0, 0, 1}}
    	};

    	SDL_GPUBufferCreateInfo vertexBufferDesc{};
    	vertexBufferDesc.size = vertices.size() * sizeof(Vertex);
    	vertexBufferDesc.usage = SDL_GPU_BUFFERUSAGE_VERTEX;
    	vertexBuffer = SDL_CreateGPUBuffer(*physicalDevice, &vertexBufferDesc);
    	if(!vertexBuffer)
    		throw std::runtime_error("Failed to create vertex buffer");

		SDL_GPUTransferBufferCreateInfo transferBufferDesc{};
    	transferBufferDesc.size = vertices.size() * sizeof(Vertex);
    	vertexBufferDesc.usage = SDL_GPU_TRANSFERBUFFERUSAGE_UPLOAD;
    	auto transferBuffer = SDL_CreateGPUTransferBuffer(*physicalDevice, &transferBufferDesc);
    	if(!transferBuffer)
    		throw std::runtime_error("Failed to create transfer buffer");

    	Vertex* transferBufferData = static_cast<Vertex *>(SDL_MapGPUTransferBuffer(*physicalDevice, transferBuffer, false));
		std::ranges::copy(vertices, transferBufferData);

    	SDL_UnmapGPUTransferBuffer(*physicalDevice, transferBuffer);

    	SDL_GPUCommandBuffer* commandBuffer = SDL_AcquireGPUCommandBuffer(*physicalDevice);
		if(!commandBuffer)
			throw std::runtime_error("Failed to acquire command buffer");
    	SDL_GPUCopyPass* copyPass = SDL_BeginGPUCopyPass(commandBuffer);

    	SDL_GPUTransferBufferLocation transferBufferLocation{};
    	transferBufferLocation.transfer_buffer = transferBuffer;
    	transferBufferLocation.offset = 0;

    	SDL_GPUBufferRegion bufferRegion{};
    	bufferRegion.buffer = vertexBuffer;
    	bufferRegion.offset = 0;
    	bufferRegion.size = vertexBufferDesc.size;

    	SDL_UploadToGPUBuffer(copyPass, &transferBufferLocation, &bufferRegion, false);
    	SDL_EndGPUCopyPass(copyPass);

    	if(!SDL_SubmitGPUCommandBuffer(commandBuffer))
    		throw std::runtime_error("Failed to submit command buffer");

    	SDL_ReleaseGPUTransferBuffer(*physicalDevice, transferBuffer);
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
    		{ vertexBuffer, 0 }
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
