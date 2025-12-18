#pragma once

#include <neonRHI/neonRHI.h>

#include "graphicsSystem.h"
#include "core/system.h"
#include "components/meshRenderer.h"

namespace Neon
{
    struct CameraUniforms
    {
        glm::mat4 view;
        glm::mat4 proj;
    };

    struct MeshUniforms
    {
        glm::mat4 model;
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
        void renderMesh(ECS::Entity entity, const MeshRenderer& meshRenderer) const;
        void renderSubMesh(const MeshRenderer &meshRenderer, int materialIndex) const;

        Rc<RHI::TextureView> getOrCreateTextureView(const Rc<RHI::Texture>& texture) const;

        mutable std::unordered_map<RHI::Texture*, Rc<RHI::TextureView>> m_textureViewCache;

        GraphicsSystem* m_graphicsSystem{};

        Rc<RHI::Device> m_device{};
        Rc<RHI::Window> m_window{};
        Rc<RHI::Pipeline> m_pipeline{};
        Rc<RHI::CommandList> m_commandList{};

        Rc<RHI::Buffer> m_cameraUniformBuffer{};
        Rc<RHI::Buffer> m_modelUniformBuffer{};
        Rc<RHI::Buffer> m_debugUniformBuffer{};
        Rc<RHI::Buffer> m_materialUniformBuffer{};
        Rc<RHI::Buffer> m_pointLightsUniformBuffer{};
    };
}
