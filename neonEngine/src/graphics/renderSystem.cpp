#include "renderSystem.h"

#include <tiny_gltf.h>

#include <neonRHI/neonRHI.h>

#include "mesh.h"
#include "components/camera.h"
#include "components/pointLight.h"
#include "core/engine.h"
#include "core/eventManager.h"
#include "core/sceneManager.h"
#include "ecs/components/transformComponent.h"
#include "events/quitEvent.h"
#include "events/windowResizeEvent.h"
#include "glm/glm.hpp"
#include "input/events/keyDownEvent.h"
#include "input/events/keyUpEvent.h"
#include "input/events/mouseButtonDownEvent.h"
#include "input/events/mouseButtonUpEvent.h"
#include "input/events/mouseMoveEvent.h"
#include "input/events/mouseWheelEvent.h"
#include "input/events/textInputEvent.h"
#include "util/file.h"

namespace Neon
{
    RenderSystem::RenderSystem(const RHI::WindowCreationOptions &windowOptions)
    {
    	window = Scope<RHI::Window>(RHI::Window::createWindow(windowOptions));
    }

    void RenderSystem::preStartup()
    {
    	window->run();
    	device = Scope<RHI::Device>(window->createDevice());

	    const auto shaderPath = "C:/Users/alikg/CLionProjects/neonEngine/neonEngine/resources/shaders/triangle.glsl";
	    const auto shader = device->createShaderFromSource(File::readFileText(shaderPath), shaderPath);
    	shader->compile();

    	RHI::VertexInputState vertexInputState{};
    	vertexInputState.addVertexBuffer<Vertex>(0);
    	vertexInputState.addVertexAttribute<glm::vec3>(0, 0);
    	vertexInputState.addVertexAttribute<glm::vec3>(0, 1);
    	vertexInputState.addVertexAttribute<glm::vec2>(0, 2);

    	RHI::DepthState depthState{};
    	depthState.hasDepthTarget = true;
    	depthState.enableDepthTest = true;

	    const RHI::RenderTargetsDescription targetsDesc{};

    	RHI::GraphicsPipelineDescription pipelineDescription{};
    	pipelineDescription.shader = shader;
    	pipelineDescription.vertexInputState = vertexInputState;
    	pipelineDescription.cullMode = RHI::CullMode::None;
    	pipelineDescription.targetsDescription = targetsDesc;
    	pipelineDescription.depthState = depthState;

    	pipeline = Scope<RHI::GraphicsPipeline>(device->createGraphicsPipeline(pipelineDescription));

    	commandList = Scope<RHI::CommandList>(device->createCommandList());

    	cameraUniformBuffer      = Scope<RHI::Buffer>(device->createUniformBuffer());
    	modelUniformBuffer       = Scope<RHI::Buffer>(device->createUniformBuffer());
    	materialsUniformBuffer   = Scope<RHI::Buffer>(device->createUniformBuffer());
    	pointLightsUniformBuffer = Scope<RHI::Buffer>(device->createUniformBuffer());
    	debugUniformBuffer       = Scope<RHI::Buffer>(device->createUniformBuffer());

    	DebugUniforms debugUniforms{};
    	debugUniforms.debugUvs = false;
    	debugUniforms.debugNormals = false;

    	commandList->begin();

    	commandList->reserveBuffer(cameraUniformBuffer.get()     , sizeof(CameraUniforms));
    	commandList->reserveBuffer(modelUniformBuffer.get()      , sizeof(MeshUniforms));
    	commandList->reserveBuffer(materialsUniformBuffer.get()  , sizeof(MaterialsUniforms));
    	commandList->reserveBuffer(pointLightsUniformBuffer.get(), sizeof(PointLightUniforms));

    	commandList->reserveBuffer(debugUniformBuffer.get(), sizeof(DebugUniforms));
    	commandList->updateBuffer(debugUniformBuffer.get(), debugUniforms);

		device->submit(commandList.get());
    }

    void RenderSystem::render()
    {
    	auto world = Engine::getSceneManager().getCurrentScene().getWorld();

	    const auto cameras = world.getComponents<Camera, Transform>();
    	if(cameras.size() < 1) return;

    	auto [camEntity, camera, camTransform] = cameras[0];

    	commandList->begin();

    	commandList->setFrameBuffer(device->getSwapChainFrameBuffer());
        commandList->setPipeline(pipeline.get());

    	commandList->clearColorTarget(0, camera.bgColor);
    	commandList->clearDepthStencil(1.0f);

    	const glm::mat4 flip = glm::scale(glm::mat4(1.0f),glm::vec3(1, 1, -1));
    	const glm::mat4 viewMatrix = glm::inverse(Transform::getWorldMatrix(camEntity) * flip);

    	CameraUniforms cameraMatrices =
		{
    		viewMatrix,
			camera.getProjectionMatrix(),
		};

		commandList->updateBuffer(cameraUniformBuffer.get(), cameraMatrices);
     	commandList->setUniformBuffer("CameraUniforms", cameraUniformBuffer.get());

    	commandList->setUniformBuffer("DebugUniforms", debugUniformBuffer.get());

    	auto meshRenderers = world.getComponents<MeshRenderer, Transform>();
    	auto pointLights = world.getComponents<PointLight, Transform>();

    	PointLightUniforms pointLightUniforms{};

    	int i = 0;
    	for (auto[entity, pointLight, transform] : pointLights)
    	{
    		pointLightUniforms.pointLights[i] =
			{
    			transform.getPosition(),
    			pointLight.power,
    			pointLight.color,
			};

    		i++;
    		if(i >= 32) return;
    	}

    	pointLightUniforms.pointLightsCount = i;

    	commandList->updateBuffer(pointLightsUniformBuffer.get(), pointLightUniforms);
    	commandList->setUniformBuffer("PointLightUniforms", pointLightsUniformBuffer.get());

     	for (auto[entity, meshRenderer, transform] : meshRenderers)
     	{
			 renderMesh(entity, meshRenderer);
     	}

        device->submit(commandList.get());
    	device->swapBuffers();
    }


    RHI::Device* RenderSystem::getDevice() const
    {
    	return device.get();
    }

    RHI::Window* RenderSystem::getWindow() const
    {
    	return window.get();
    }

    void RenderSystem::renderMesh(const EntityID entity, const MeshRenderer& meshRenderer) const
    {
    	if(meshRenderer.mesh == nullptr) return;

    	const glm::mat4 modelMatrix = Transform::getWorldMatrix(entity);

    	MeshUniforms modelUniforms =
		{
    		modelMatrix
		};

    	commandList->updateBuffer(modelUniformBuffer.get(), modelUniforms);
    	commandList->setUniformBuffer("ModelUniforms", modelUniformBuffer.get());

	    constexpr int MAX_MATERIALS = 64;
	    const int materialsInUse = std::min(static_cast<int>(meshRenderer.materials.size()), MAX_MATERIALS);

    	MaterialsUniforms materialsUniforms{};

    	for(int i = 0; i < materialsInUse; i++)
    	{
    		// bind texture somewhere here
    		int useAlbedoTexture = false;
		    const AssetRef<Material> mat = meshRenderer.getMaterial();
    		auto albedoTexture = mat->albedoTexture;
			if(albedoTexture != nullptr)
			{
				useAlbedoTexture = true;
				commandList->setTexture("albedoTextures", i, mat->albedoTexture->getTexture());
				commandList->setSampler("albedoTextures", i, mat->albedoTexture->getSampler());
			}

		    const MaterialUniforms materialUniforms =
			{
    			mat->roughness,
				mat->metalness,
				mat->albedo,
				useAlbedoTexture
			};

    		materialsUniforms.materials[i] = materialUniforms;
    		materialsUniforms.count = i+1;
    	}

    	commandList->updateBuffer(materialsUniformBuffer.get(), materialsUniforms);
    	commandList->setUniformBuffer("MaterialsUniforms", materialsUniformBuffer.get());

    	commandList->setVertexBuffer(0, meshRenderer.mesh->vertexBuffer.get());
    	commandList->setIndexBuffer(meshRenderer.mesh->indexBuffer.get(), RHI::IndexFormat::UInt32);
    	commandList->drawIndexed(meshRenderer.mesh->indices.size());
    }

    void RenderSystem::shutdown()
    {
        window->close();
    }

    void RenderSystem::preUpdate()
    {
	    std::vector<RHI::Event> events = window->pollEvents();

    	EventManager& eventManager = Engine::getEventManager();

    	for(const auto event : events)
    	{
    		switch (event.type)
    		{
    			case RHI::Event::Type::Quit:
    				eventManager.queueEvent(new QuitEvent());
    				break;
    			case RHI::Event::Type::WindowResize:
    				eventManager.queueEvent(new WindowResizeEvent(event.window.width, event.window.height));
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
    				eventManager.queueEvent(new TextInputEvent(event.text.text));
    				break;
    		}
    	}
    }
}
