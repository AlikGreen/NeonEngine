#pragma once

#include <neonRHI/neonRHI.h>
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
        explicit RenderSystem(const RHI::WindowCreationOptions &windowOptions);

        void preStartup() override;
        void shutdown() override;
        void preUpdate() override;
        void render() override;
        void postRender() override;

        [[nodiscard]] RHI::Device* getDevice() const;
        [[nodiscard]] RHI::Window* getWindow() const;
    private:
        void renderMesh(ECS::Entity entity, const MeshRenderer& meshRenderer) const;

        void renderSubMesh(const MeshRenderer &meshRenderer, int materialIndex) const;

        RHI::TextureView* getOrCreateTextureView(const AssetRef<RHI::Texture>& texture) const;

        mutable std::unordered_map<uint64_t, Box<RHI::TextureView>> textureViewCache;

        Box<RHI::Window> window{};
        Box<RHI::Device> device{};

        Box<RHI::Pipeline> pipeline{};
        Box<RHI::CommandList> commandList{};

        Box<RHI::Buffer> cameraUniformBuffer{};
        Box<RHI::Buffer> modelUniformBuffer{};
        Box<RHI::Buffer> debugUniformBuffer{};
        Box<RHI::Buffer> materialUniformBuffer{};
        Box<RHI::Buffer> pointLightsUniformBuffer{};
    };
}
