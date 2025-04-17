#include "renderSystem.h"

#include <iostream>


#include "../neonEngine.h"
#include "glm/glm.hpp"

namespace Neon
{
    SDL_GPUShader* LoadShader(
	SDL_GPUDevice* device,
	SDL_GPUShaderStage stage,
	const char* shaderFilename,
	Uint32 samplerCount,
	Uint32 uniformBufferCount,
	Uint32 storageBufferCount,
	Uint32 storageTextureCount
) {
	size_t codeSize;
	void* code = SDL_LoadFile(shaderFilename, &codeSize);
	if (code == nullptr)
	{
		SDL_Log("Failed to load shader from disk! %s", shaderFilename);
		return nullptr;
	}

	SDL_GPUShaderCreateInfo shaderInfo;
	shaderInfo.code = static_cast<const Uint8 *>(code);
	shaderInfo.code_size = codeSize;
	shaderInfo.entrypoint = "main";
	shaderInfo.format = SDL_GPU_SHADERFORMAT_SPIRV;
	shaderInfo.stage = stage;
	shaderInfo.num_samplers = samplerCount;
	shaderInfo.num_uniform_buffers = uniformBufferCount;
	shaderInfo.num_storage_buffers = storageBufferCount;
	shaderInfo.num_storage_textures = storageTextureCount;

	SDL_GPUShader* shader = SDL_CreateGPUShader(device, &shaderInfo);
	if (shader == nullptr)
	{
		SDL_Log("Failed to create shader!");
		SDL_free(code);
		return nullptr;
	}

	SDL_free(code);
	return shader;
}

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


        device = SDL_CreateGPUDevice(SDL_GPU_SHADERFORMAT_SPIRV, true, nullptr);
    	//  | SDL_GPU_SHADERFORMAT_MSL | SDL_GPU_SHADERFORMAT_DXIL
        if(!device)
            throw std::runtime_error("Failed to create GPU device");

        if(!SDL_ClaimWindowForGPUDevice(device, *window))
            throw std::runtime_error("Failed to claim SDL window for gpu");

    	SDL_GPUShader* vertexShader = LoadShader(device, SDL_GPU_SHADERSTAGE_VERTEX, "C:/Users/alikg/CLionProjects/neonEngine/neonEngine/resources/shaders/simpleVert.spv", 0, 0, 0, 0);
		if(!vertexShader)
			throw std::runtime_error("Failed to load vertex shader");

    	SDL_GPUShader* fragmentShader = LoadShader(device, SDL_GPU_SHADERSTAGE_FRAGMENT, "C:/Users/alikg/CLionProjects/neonEngine/neonEngine/resources/shaders/simpleFrag.spv", 0, 0, 0, 0);
		if(!fragmentShader)
			throw std::runtime_error("Failed to load fragment shader");

    	SDL_GPUColorTargetDescription colorTargetDesc{};
    	colorTargetDesc.format = SDL_GetGPUSwapchainTextureFormat(device, *window);
        const std::vector colorTargets = {colorTargetDesc};

    	std::vector<SDL_GPUVertexAttribute> vertexAttributes =
    	{
    		SDL_GPUVertexAttribute(0, 0, SDL_GPU_VERTEXELEMENTFORMAT_FLOAT2, 0),
    		SDL_GPUVertexAttribute(1, 0, SDL_GPU_VERTEXELEMENTFORMAT_FLOAT3, sizeof(glm::vec2))
    	};

    	std::vector<SDL_GPUVertexBufferDescription> vertexBufferDescriptions =
    	{
    		SDL_GPUVertexBufferDescription(0, sizeof(Vertex))
    	};

    	SDL_GPUVertexInputState vertexInputState{};
    	vertexInputState.vertex_attributes = vertexAttributes.data();
    	vertexInputState.num_vertex_attributes = vertexAttributes.size();
    	vertexInputState.vertex_buffer_descriptions = vertexBufferDescriptions.data();
    	vertexInputState.num_vertex_buffers = vertexBufferDescriptions.size();

    	SDL_GPUGraphicsPipelineCreateInfo pipelineDesc{};
    	pipelineDesc.vertex_shader = vertexShader;
    	pipelineDesc.fragment_shader = fragmentShader;
    	pipelineDesc.primitive_type = SDL_GPU_PRIMITIVETYPE_TRIANGLELIST;
    	pipelineDesc.rasterizer_state.fill_mode = SDL_GPU_FILLMODE_FILL;
    	pipelineDesc.rasterizer_state.cull_mode = SDL_GPU_CULLMODE_BACK;
    	pipelineDesc.target_info.color_target_descriptions = colorTargets.data();
    	pipelineDesc.target_info.num_color_targets = colorTargets.size();
    	pipelineDesc.vertex_input_state = vertexInputState;


    	pipeline = SDL_CreateGPUGraphicsPipeline(device, &pipelineDesc);
    	if(!pipeline)
    		throw std::runtime_error("Failed to create graphics pipeline");

    	SDL_ReleaseGPUShader(device, vertexShader);
    	SDL_ReleaseGPUShader(device, fragmentShader);

    	std::vector<Vertex> vertices =
    	{
    		{{-0.5, -0.5}, {1, 0, 0}},
			{{0.5, -0.5}, {0, 1, 0}},
			{{0, 0.5}, {0, 0, 1}}
    	};

    	SDL_GPUBufferCreateInfo vertexBufferDesc{};
    	vertexBufferDesc.size = vertices.size() * sizeof(Vertex);
    	vertexBufferDesc.usage = SDL_GPU_BUFFERUSAGE_VERTEX;
    	vertexBuffer = SDL_CreateGPUBuffer(device, &vertexBufferDesc);
    	if(!vertexBuffer)
    		throw std::runtime_error("Failed to create vertex buffer");

		SDL_GPUTransferBufferCreateInfo transferBufferDesc{};
    	transferBufferDesc.size = vertices.size() * sizeof(Vertex);
    	vertexBufferDesc.usage = SDL_GPU_TRANSFERBUFFERUSAGE_UPLOAD;
    	auto transferBuffer = SDL_CreateGPUTransferBuffer(device, &transferBufferDesc);
    	if(!transferBuffer)
    		throw std::runtime_error("Failed to create transfer buffer");

    	Vertex* transferBufferData = static_cast<Vertex *>(SDL_MapGPUTransferBuffer(device, transferBuffer, false));
		std::ranges::copy(vertices, transferBufferData);

    	SDL_UnmapGPUTransferBuffer(device, transferBuffer);

    	SDL_GPUCommandBuffer* commandBuffer = SDL_AcquireGPUCommandBuffer(device);
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

    	SDL_ReleaseGPUTransferBuffer(device, transferBuffer);

    	SDL_ShowWindow(*window);
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

        SDL_GPUCommandBuffer* commandBuffer = SDL_AcquireGPUCommandBuffer(device);
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

        std::vector colorTargets{colorTarget};

        SDL_GPURenderPass* renderPass = SDL_BeginGPURenderPass(commandBuffer, colorTargets.data(), colorTargets.size(), nullptr);
    	SDL_BindGPUGraphicsPipeline(renderPass, pipeline);

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

    void RenderSystem::shutdown()
    {
        window->close();
    }
}
