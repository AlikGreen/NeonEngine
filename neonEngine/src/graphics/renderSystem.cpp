#include "renderSystem.h"


#include "mesh.h"
#include "core/engine.h"
#include "components/meshRenderer.h"
#include "backend/colorTarget.h"
#include "backend/commandBuffer.h"
#include "backend/depthStencilTarget.h"
#include "backend/shader.h"
#include "backend/texture.h"
#include "backend/buffers/vertexBuffer.h"
#include "ecs/ECSSystem.h"
#include "ecs/components/transformComponent.h"
#include "glm/glm.hpp"
#include "glm/ext/matrix_transform.hpp"

namespace Neon
{
    RenderSystem::RenderSystem(const WindowOptions &windowOptions)
    {
    	window = new Window(windowOptions);
    }

    void RenderSystem::preStartup()
    {
    	window->run();
    	physicalDevice = new PhysicalDevice(window);

    	auto shader = new Shader("C:/Users/alikg/CLionProjects/neonEngine/neonEngine/resources/shaders/triangle.glsl");
    	shader->compile();

    	VertexInputState vertexInputState{};
    	vertexInputState.addVertexBuffer<Vertex>(0);
    	vertexInputState.addVertexAttribute<glm::vec3>(0, 0);
    	vertexInputState.addVertexAttribute<glm::vec3>(0, 1);
    	vertexInputState.addVertexAttribute<glm::vec2>(0, 2);

    	DepthState depthState{};
    	depthState.hasDepthTarget = true;
    	depthState.enableDepthTest = true;

    	RenderTargetsDescription targetsDesc{};
    	targetsDesc.colorTargetFormats = {physicalDevice->getSwapchainTextureFormat()};
    	targetsDesc.depthTargetFormat = TextureFormat::D32Float;

    	GraphicsPipelineDescription pipelineDescription{};
    	pipelineDescription.shader = shader;
    	pipelineDescription.vertexInputState = vertexInputState;
    	pipelineDescription.cullMode = CullMode::None;
    	pipelineDescription.targetsDescription = targetsDesc;
    	pipelineDescription.depthState = depthState;


    	pipeline = new GraphicsPipeline(pipelineDescription);

    	shader->dispose();

    	depthTexture = new Texture(TextureType::Texture2D, TextureFormat::D32Float, 1920, 1080, TextureUsage::DepthStencilTarget);
    }

    void RenderSystem::render()
    {
    	const CommandBuffer commandBuffer = physicalDevice->acquireCommandBuffer();

	    const Texture swapChainTexture = commandBuffer.waitForSwapChainTexture();

    	auto colorTarget = ColorTarget(swapChainTexture);
    	colorTarget.clearColor = {0.0f, 0.6f, 0.0f ,1.0f};

	    const auto depthTarget = new DepthStencilTarget(*depthTexture);

        RenderPass renderPass = commandBuffer.beginRenderPass({colorTarget}, depthTarget);
    	renderPass.bindPipeline(pipeline);

    	auto* ecsSystem = Engine::getInstance()->getSystem<ECSSystem>();
    	auto components = ecsSystem->getWorld()->getComponents<MeshRenderer, Transform>();

    	glm::vec4 tintColor = {0.0f, 0.5f, 0.2f, 1.0f};
    	commandBuffer.pushFragmentUniformData(tintColor, 0);

    	for (auto[entity, meshRenderer, transform] : components)
    	{
			renderMesh(meshRenderer, renderPass, commandBuffer);
    	}

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

    void RenderSystem::renderMesh(const MeshRenderer& meshRenderer, const RenderPass renderPass, const CommandBuffer &commandBuffer)
    {
    	glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.4f, 0.0f, 0.0f));
    	commandBuffer.pushVertexUniformData(model, 0);

    	const std::vector<SDL_GPUBufferBinding> bufferBindings =
		{
    		{ *meshRenderer.mesh.vertexBuffer, 0 }
		};

    	renderPass.bindVertexBuffers(0, bufferBindings);
    	renderPass.draw(3, 1);
    }

    void RenderSystem::shutdown()
    {
        window->close();
    }
}
