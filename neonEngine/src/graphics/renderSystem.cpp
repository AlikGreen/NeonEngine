#include "renderSystem.h"

#include <tiny_gltf.h>

#include <neonRHI/neonRHI.h>

#include "graphicsSystem.h"
#include "mesh.h"
#include "asset/assetManager.h"
#include "components/camera.h"
#include "components/pointLight.h"
#include "core/engine.h"
#include "core/eventManager.h"
#include "core/sceneManager.h"
#include "core/components/transformComponent.h"
#include "events/windowResizeEvent.h"
#include "glm/glm.hpp"
#include "glm/gtx/dual_quaternion.hpp"

namespace Neon
{
    void RenderSystem::preStartup()
    {
    	m_graphicsSystem = Engine::getSystem<GraphicsSystem>();

    	m_window = m_graphicsSystem->getWindow();
    	m_device = m_graphicsSystem->getDevice();

    	AssetManager& assetManager = Engine::getAssetManager();
	    const auto shaderHandle = assetManager.loadAsset<Rc<RHI::Shader>>("shaders/pbr.glsl");
    	const auto& shader = assetManager.getAsset<Rc<RHI::Shader>>(shaderHandle);

    	shader->compile();

    	RHI::InputLayout vertexInputState{};
    	vertexInputState.addVertexBuffer<Vertex>(0);
    	vertexInputState.addVertexAttribute<glm::vec3>(0, 0);
    	vertexInputState.addVertexAttribute<glm::vec3>(0, 1);
    	vertexInputState.addVertexAttribute<glm::vec2>(0, 2);

    	RHI::DepthState depthState{};
    	depthState.hasDepthTarget  = true;
    	depthState.enableDepthTest = true;
    	depthState.enableDepthWrite = true;

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

    	m_commandList = m_device->createCommandList();

    	m_cameraUniformBuffer      = m_device->createUniformBuffer();
    	m_modelUniformBuffer       = m_device->createUniformBuffer();
    	m_materialUniformBuffer    = m_device->createUniformBuffer();
    	m_pointLightsUniformBuffer = m_device->createUniformBuffer();
    	m_debugUniformBuffer       = m_device->createUniformBuffer();

    	DebugUniforms debugUniforms{};
    	debugUniforms.debugUvs     = false;
    	debugUniforms.debugNormals = false;

    	m_commandList->begin();

    	m_commandList->reserveBuffer(m_cameraUniformBuffer     , sizeof(CameraUniforms));
    	m_commandList->reserveBuffer(m_modelUniformBuffer      , sizeof(MeshUniforms));
    	m_commandList->reserveBuffer(m_materialUniformBuffer   , sizeof(MaterialUniforms));
    	m_commandList->reserveBuffer(m_pointLightsUniformBuffer, sizeof(PointLightUniforms));

    	m_commandList->reserveBuffer(m_debugUniformBuffer, sizeof(DebugUniforms));
    	m_commandList->updateBuffer( m_debugUniformBuffer, debugUniforms);

		m_device->submit(m_commandList);
    }

    void RenderSystem::postStartup()
    {
    	auto& world = Engine::getSceneManager().getCurrentScene().getRegistry();

    	const auto cameras = world.view<Camera>();

    	for(auto [entity, camera] : cameras)
    	{
    		if(camera.matchWindowSize)
    		{
    			camera.setWidth(m_window->getWidth());
    			camera.setHeight(m_window->getHeight());
    		}
    	}
    }

    void RenderSystem::render()
    {
    	auto& world = Engine::getSceneManager().getCurrentScene().getRegistry();

	    const auto cameras = world.view<Camera, Transform>();
    	if(cameras.size() < 1) return;

    	auto [camEntity, camera, camTransform] = cameras.at(0);

    	m_commandList->begin();

	    const Rc<RHI::Framebuffer> framebuffer = camera.getFramebuffer();
    	m_commandList->setFramebuffer(framebuffer);
        m_commandList->setPipeline(m_pipeline);

    	m_commandList->clearColorTarget(0, camera.bgColor);
    	m_commandList->clearDepthStencil(1.0f);

    	const glm::mat4 flip = glm::scale(glm::mat4(1.0f),glm::vec3(1, 1, -1));
    	const glm::mat4 viewMatrix = glm::inverse(Transform::getWorldMatrix(camEntity) * flip);

    	CameraUniforms cameraMatrices =
		{
    		viewMatrix,
			camera.getProjectionMatrix(),
		};

		m_commandList->updateBuffer(m_cameraUniformBuffer, cameraMatrices);
     	m_commandList->setUniformBuffer("CameraUniforms", m_cameraUniformBuffer);

    	m_commandList->setUniformBuffer("DebugUniforms", m_debugUniformBuffer);

	    const auto& meshRenderers = world.view<MeshRenderer, Transform>();
	    const auto& pointLights = world.view<PointLight, Transform>();

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

    	m_commandList->updateBuffer(m_pointLightsUniformBuffer, pointLightUniforms);
    	m_commandList->setUniformBuffer("PointLightUniforms", m_pointLightsUniformBuffer);

    	std::vector<std::pair<ECS::Entity, MeshRenderer&>> orderedAndCulledEntities{};

     	for (auto[entity, meshRenderer, transform] : meshRenderers)
     	{
     		glm::mat4 worldMat = Transform::getWorldMatrix(entity);
     		if(camera.getFrustum(glm::inverse(worldMat)).intersects(meshRenderer.mesh->getBounds()))
     		{
     			orderedAndCulledEntities.emplace_back(entity, meshRenderer);
     		}
     	}

	    for (const auto& [entity, meshRenderer]: orderedAndCulledEntities)
	    {
	    	renderMesh(entity, meshRenderer);
	    }

        m_device->submit(m_commandList);
    }


    void RenderSystem::event(Event *event)
    {
	    if(const auto resize = dynamic_cast<WindowResizeEvent*>(event))
	    {
	    	auto& world = Engine::getSceneManager().getCurrentScene().getRegistry();
	    	const auto cameras = world.view<Camera>();

	    	for(auto [entity, camera] : cameras)
	    	{
	    		if(camera.matchWindowSize)
	    		{
	    			camera.setWidth(resize->width);
	    			camera.setHeight(resize->height);
	    		}
	    	}
	    }
    }

    void RenderSystem::renderMesh(const ECS::Entity entity, const MeshRenderer& meshRenderer) const
    {
    	if(meshRenderer.mesh == nullptr) return;

    	const glm::mat4 modelMatrix = Transform::getWorldMatrix(entity);

    	MeshUniforms modelUniforms =
		{
    		modelMatrix
		};

    	m_commandList->updateBuffer(m_modelUniformBuffer, modelUniforms);
    	m_commandList->setUniformBuffer("ModelUniforms", m_modelUniformBuffer);

		for(int i = 0; i < meshRenderer.materials.size(); i++)
		{
			renderSubMesh(meshRenderer, i);
		}
    }

	void RenderSystem::renderSubMesh(const MeshRenderer& meshRenderer, const int materialIndex) const
    {
    	if(meshRenderer.materials.size() < materialIndex ||
    		meshRenderer.mesh->getPrimitives().size() < materialIndex) return;

    	int useAlbedoTexture = false;
    	const AssetRef<Material> mat = meshRenderer.materials[materialIndex];
    	const auto albedoTexture = mat->albedoTexture;
    	if(albedoTexture != nullptr)
    	{
    		useAlbedoTexture = true;

    		const Rc<RHI::TextureView>& view = getOrCreateTextureView(albedoTexture->getTexture());

    		m_commandList->setTexture("albedoTexture", view);
    		m_commandList->setSampler("albedoTexture", mat->albedoTexture->getSampler());
    	}

    	MaterialUniforms materialUniforms =
		{
    		mat->roughness,
			mat->metalness,
			mat->albedo,
			useAlbedoTexture
		};

	    const Primitive primitive = meshRenderer.mesh->getPrimitives().at(materialIndex);

    	m_commandList->updateBuffer(m_materialUniformBuffer, materialUniforms);
    	m_commandList->setUniformBuffer("MaterialUniforms", m_materialUniformBuffer);

    	m_commandList->setVertexBuffer(0, meshRenderer.mesh->getVertexBuffer());
    	m_commandList->setIndexBuffer(meshRenderer.mesh->getIndexBuffer(), RHI::IndexFormat::UInt32);
    	m_commandList->drawIndexed(primitive.indexCount, 1, primitive.indexStart);
    }


	Rc<RHI::TextureView> RenderSystem::getOrCreateTextureView(const Rc<RHI::Texture>& texture) const
    {
    	if(texture == nullptr) return nullptr;

    	if(m_textureViewCache.contains(texture.get()))
			return m_textureViewCache.at(texture.get());

    	const RHI::TextureViewDescription viewDesc{ texture };
    	Rc<RHI::TextureView> view = m_device->createTextureView(viewDesc);
    	m_textureViewCache.emplace(texture.get(), view);

    	return view;
    }
}
