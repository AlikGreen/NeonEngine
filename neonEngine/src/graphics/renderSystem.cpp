#include "renderSystem.h"

#include <tiny_gltf.h>


#include "mesh.h"
#include "api/commandList.h"
#include "api/window.h"
#include "api/descriptions/windowCreationOptions.h"
#include "api/enums/shaderType.h"
#include "components/camera.h"
#include "components/pointLight.h"
#include "core/engine.h"
#include "core/sceneManager.h"
#include "debug/logger.h"
#include "ecs/components/transformComponent.h"
#include "glm/glm.hpp"
#include "util/file.h"

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

	    const auto shaderPath = "C:/Users/alikg/CLionProjects/neonEngine/neonEngine/resources/shaders/triangle.glsl";
	    const auto shader = device->createShaderFromSource(File::readFileText(shaderPath), shaderPath);
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

    	TextureDescription depthTextureDesc{};
    	depthTextureDesc.width = window->getWidth();
    	depthTextureDesc.height = window->getHeight();
    	depthTextureDesc.usage = TextureUsage::DepthStencilTarget;
    	depthTextureDesc.format = TextureFormat::D32FloatS8Uint;

    	depthTexture = device->createTexture(depthTextureDesc);

    	commandList = device->createCommandList();

    	cameraUniformBuffer      = device->createUniformBuffer();
    	modelUniformBuffer       = device->createUniformBuffer();
    	materialsUniformBuffer    = device->createUniformBuffer();
    	pointLightsUniformBuffer = device->createUniformBuffer();
    	debugUniformBuffer       = device->createUniformBuffer();

    	DebugUniforms debugUniforms{};
    	debugUniforms.debugUvs = false;
    	debugUniforms.debugNormals = false;

    	commandList->begin();

    	commandList->reserveBuffer(cameraUniformBuffer, sizeof(CameraUniforms));
    	commandList->reserveBuffer(modelUniformBuffer, sizeof(MeshUniforms));
    	commandList->reserveBuffer(materialsUniformBuffer, sizeof(MaterialsUniforms));
    	commandList->reserveBuffer(pointLightsUniformBuffer, sizeof(PointLightUniforms));

    	commandList->reserveBuffer(debugUniformBuffer, sizeof(DebugUniforms));
    	commandList->updateBuffer(debugUniformBuffer, debugUniforms);

		device->submit(commandList);
    }

    void RenderSystem::render()
    {
    	auto world = Engine::getSceneManager().getCurrentScene().getWorld();

	    const auto cameras = world.getComponents<Camera, Transform>();
    	if(cameras.size() < 1) return;

    	auto [camEntity, camera, camTransform] = cameras[0];

    	commandList->begin();

    	commandList->setFrameBuffer(device->getSwapChainFrameBuffer());
        commandList->setPipeline(pipeline);

    	commandList->clearColorTarget(0, camera.bgColor);
    	commandList->clearDepthStencil(1.0f);

    	const glm::mat4 flip = glm::scale(glm::mat4(1.0f),glm::vec3(1, 1, -1));
    	const glm::mat4 viewMatrix = glm::inverse(Transform::getWorldMatrix(camEntity) * flip);

    	CameraUniforms cameraMatrices =
		{
    		viewMatrix,
			camera.getProjectionMatrix(),
		};

		commandList->updateBuffer(cameraUniformBuffer, cameraMatrices);
     	commandList->setUniformBuffer(0, ShaderType::Vertex, cameraUniformBuffer);

    	commandList->setUniformBuffer(4, ShaderType::Fragment, debugUniformBuffer);

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

    	commandList->updateBuffer(pointLightsUniformBuffer, pointLightUniforms);
    	commandList->setUniformBuffer(3, ShaderType::Fragment, pointLightsUniformBuffer);

     	for (auto[entity, meshRenderer, transform] : meshRenderers)
     	{
			 renderMesh(entity, meshRenderer);
     	}

        device->submit(commandList);
    	device->swapBuffers();
    }


    Ref<Device> RenderSystem::getDevice() const
    {
    	return device;
    }

    Ref<Window> RenderSystem::getWindow() const
    {
    	return window;
    }

    void RenderSystem::renderMesh(const EntityID entity, const MeshRenderer& meshRenderer) const
    {
    	if(meshRenderer.mesh == nullptr) return;

    	const glm::mat4 modelMatrix = Transform::getWorldMatrix(entity);

    	MeshUniforms modelUniforms =
		{
    		modelMatrix
		};

    	commandList->updateBuffer(modelUniformBuffer, modelUniforms);
    	commandList->setUniformBuffer(1, ShaderType::Vertex, modelUniformBuffer);

    	MaterialsUniforms materialsUniforms{};

    	for(int i = 0; i < meshRenderer.materials.size() && i < 64; i++)
    	{
		    const MaterialUniforms materialUniforms =
			{
    			meshRenderer.getMaterial()->roughness,
				meshRenderer.getMaterial()->metalness,
				meshRenderer.getMaterial()->albedo
			};

    		materialsUniforms.materials[i] = materialUniforms;
    		materialsUniforms.count = i;
    	}

    	commandList->updateBuffer(materialsUniformBuffer, materialsUniforms);
    	commandList->setUniformBuffer(2, ShaderType::Fragment, materialsUniformBuffer);

    	commandList->setVertexBuffer(0, meshRenderer.mesh->vertexBuffer);
    	commandList->setIndexBuffer(meshRenderer.mesh->indexBuffer, IndexFormat::UInt32);
    	commandList->drawIndexed(meshRenderer.mesh->indices.size());
    }

    void RenderSystem::shutdown()
    {
        window->close();
    }

    void RenderSystem::preUpdate()
    {
	    window->pollEvents();
    }
}
