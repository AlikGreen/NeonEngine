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
        alignas(16) glm::vec3 color;
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
        void render() override;
        void event(Event *event) override;
    private:
        void renderScene(ECS::Entity camEntity, Camera& camera);
        void renderMesh(const Rc<RHI::CommandList>& cl, ECS::Entity entity, const MeshRenderer& meshRenderer);
        void renderSubMesh(const Rc<RHI::CommandList>& cl, const MeshRenderer &meshRenderer, int materialIndex);

        void updateFramebuffer();

        Rc<RHI::Framebuffer> getOrCreateCameraFramebuffer(const Rc<RenderTarget> &target) const;

        mutable std::unordered_map<Rc<RenderTarget>, Rc<RHI::Framebuffer>> m_cameraFramebufferCache;

        GraphicsSystem* m_graphicsSystem{};

        Rc<RHI::Device> m_device{};
        Rc<RHI::Window> m_window{};

        Rc<RHI::Framebuffer> m_framebuffer{};
        Rc<RHI::Pipeline> m_currentScenePipeline{};

        Rc<RHI::Buffer> m_cameraUniformBuffer{};
        Rc<RHI::Buffer> m_modelUniformBuffer{};
        Rc<RHI::Buffer> m_pointLightsUniformBuffer{};

        Mesh m_screenMesh;
    };
}
