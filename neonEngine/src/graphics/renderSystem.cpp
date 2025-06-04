#include "renderSystem.h"


#include "mesh.h"
#include "api/commandList.h"
#include "api/window.h"
#include "api/descriptions/windowCreationOptions.h"
#include "api/enums/shaderType.h"
#include "core/engine.h"
#include "components/meshRenderer.h"
#include "debug/logger.h"
#include "ecs/ECSSystem.h"
#include "ecs/components/transformComponent.h"
#include "glm/glm.hpp"
#include "glm/ext/matrix_transform.hpp"

namespace Neon
{
    RenderSystem::RenderSystem(const WindowCreationOptions &windowOptions)
    {
    	window = Window::createWindow(windowOptions);
    }

    void RenderSystem::preStartup()
    {
    	window->run();
    	device = window->createDevice();

	    const auto shader = device->createShaderFromPath("C:/Users/alikg/CLionProjects/neonEngine/neonEngine/resources/shaders/triangle.glsl");
    	shader->compile();

    	VertexInputState vertexInputState{};
    	vertexInputState.addVertexBuffer<Vertex>(0);
    	vertexInputState.addVertexAttribute<glm::vec3>(0, 0);
    	vertexInputState.addVertexAttribute<glm::vec3>(0, 1);
    	vertexInputState.addVertexAttribute<glm::vec2>(0, 2);

    	DepthState depthState{};
    	depthState.hasDepthTarget = true;
    	depthState.enableDepthTest = true;

	    const RenderTargetsDescription targetsDesc{};

    	GraphicsPipelineDescription pipelineDescription{};
    	pipelineDescription.shader = shader;
    	pipelineDescription.vertexInputState = vertexInputState;
    	pipelineDescription.cullMode = CullMode::None;
    	pipelineDescription.targetsDescription = targetsDesc;
    	pipelineDescription.depthState = depthState;

    	pipeline = device->createGraphicsPipeline(pipelineDescription);

    	depthTexture = device->createTexture2D(window->getWidth(), window->getHeight(), TextureUsage::DepthStencilTarget, TextureFormat::D32Float);

    	commandList = device->createCommandList();

    	glm::vec4 tintColor = {0.8f, 0.3f, 0.2f, 1.0f};
    	tintColorUniformBuffer = device->createUniformBuffer<glm::vec4>(tintColor);
    	glm::vec4 model = glm::vec4(0.0f, 0.5f, 0.0f, 0.0f);
    	mpvUniformBuffer = device->createUniformBuffer<glm::vec4>(model);
    }

    void RenderSystem::render()
    {
    	commandList->begin();

    	commandList->setFrameBuffer(device->getSwapChainFrameBuffer());
        commandList->setPipeline(pipeline);

    	commandList->clearColorTarget(0, {0.0f, 0.6f, 0.0f, 1.0f});
    	commandList->clearDepthStencil(1.0f);

     	auto* ecsSystem = Engine::getSystem<ECSSystem>();
     	auto components = ecsSystem->getWorld()->getComponents<MeshRenderer, Transform>();

     	commandList->setUniformBuffer(1, ShaderType::Fragment, tintColorUniformBuffer);

     	for (auto[entity, meshRenderer, transform] : components)
     	{
			 renderMesh(meshRenderer);
     	}

        device->submitCommandList(commandList);
    	device->swapBuffers();

    	window->pollEvents();
    }


    Ref<Device> RenderSystem::getDevice() const
    {
    	return device;
    }

    Ref<Window> RenderSystem::getWindow() const
    {
    	return window;
    }

    void RenderSystem::renderMesh(const MeshRenderer& meshRenderer) const
    {
    	static float x = 0.0f;
    	x+= 0.0001f;
    	float model[] = {x, 0.5f, 0.0f, 0.0f};

    	commandList->updateBuffer<float[4]>(mpvUniformBuffer, model);
    	commandList->setUniformBuffer(0, ShaderType::Vertex, mpvUniformBuffer);

    	commandList->setVertexBuffer(0, meshRenderer.mesh->vertexBuffer);
    	commandList->setIndexBuffer(meshRenderer.mesh->indexBuffer, IndexFormat::UInt32);
    	commandList->drawIndexed(meshRenderer.mesh->indices.size());
    }

    void RenderSystem::shutdown()
    {
        window->close();
    }
}
