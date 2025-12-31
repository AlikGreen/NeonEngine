#pragma once

#include <neonRHI/neonRHI.h>

#include "graphicsSystem.h"
#include "components/camera.h"
#include "core/system.h"
#include "components/meshRenderer.h"
#include "core/components/transformComponent.h"

namespace Neon
{
    struct CameraUniforms
    {
        glm::mat4 view;
        glm::mat4 proj;
    };

    struct MeshUniforms
    {
        glm::mat4 model{};
        Primitive primitives[64]{};
    };

    struct DebugUniforms
    {
        int debugUvs = false;
        int debugNormals = false;
    };

    struct MaterialUniforms
    {
        float roughness;
        float metalness;
        alignas(16) glm::vec4 albedo;
        int useAlbedoTexture;
    };

    struct PointLightUniform
    {
        glm::vec3 position;
        float power;
        glm::vec3 color;
    };

    struct PointLightUniforms
    {
        int pointLightsCount{};
        alignas(16) PointLightUniform pointLights[32]{};
    };

    class RenderSystem final : public System
    {
    public:
        void preStartup() override;
        void postStartup() override;
        void render() override;
        void event(Event *event) override;
    private:
        void createSkyboxRenderPipeline();

        void renderMesh(const Rc<RHI::CommandList>& cl, ECS::Entity entity, const MeshRenderer& meshRenderer);
        void renderSubMesh(const Rc<RHI::CommandList>& cl, const MeshRenderer &meshRenderer, int materialIndex);

        AssetRef<Rc<RHI::Texture>> m_skybox;
        Rc<RHI::Sampler> m_skyboxSampler;

        Rc<RHI::TextureView> getOrCreateTextureView(const AssetRef<Rc<RHI::Texture>>& texture) const;
        Rc<RHI::TextureView> getOrCreateTextureView(const AssetRef<Rc<RHI::Texture>>& texture, const RHI::TextureViewDescription& viewDesc) const;

        mutable std::unordered_map<AssetHandle, Rc<RHI::TextureView>> m_textureViewCache;
        mutable std::unordered_map<AssetHandle, Rc<RHI::TextureView>> m_cubeMapCache;

        GraphicsSystem* m_graphicsSystem{};

        Rc<RHI::Device> m_device{};
        Rc<RHI::Window> m_window{};

        Rc<RHI::Pipeline> m_currentScenePipeline{};
        Rc<RHI::Pipeline> m_skyboxPipeline{};

        Rc<RHI::Buffer> m_cameraUniformBuffer{};
        Rc<RHI::Buffer> m_modelUniformBuffer{};
        Rc<RHI::Buffer> m_pointLightsUniformBuffer{};

        Rc<RHI::Buffer> m_screenQuadVertexBuffer{};
        Rc<RHI::Buffer> m_screenQuadIndexBuffer{};
    };
}
