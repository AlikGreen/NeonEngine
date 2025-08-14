#pragma once

#include <neonRHI/neonRHI.h>
#include "core/system.h"
#include "components/meshRenderer.h"
#include "ecs/components/transformComponent.h"

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

    struct MaterialsUniforms
    {
        int count{};
        MaterialUniforms materials[64]{};
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
        explicit RenderSystem(const NRHI::WindowCreationOptions &windowOptions);

        void preStartup() override;
        void shutdown() override;
        void preUpdate() override;
        void render() override;

        [[nodiscard]] Ref<NRHI::Device> getDevice() const;
        [[nodiscard]] Ref<NRHI::Window> getWindow() const;
    private:
        void renderMesh(EntityID entity, const MeshRenderer& meshRenderer) const;

        Ref<NRHI::Window> window{};
        Ref<NRHI::Device> device{};

        Ref<NRHI::GraphicsPipeline> pipeline{};
        Ref<NRHI::CommandList> commandList{};

        Ref<NRHI::Buffer> cameraUniformBuffer{};
        Ref<NRHI::Buffer> modelUniformBuffer{};
        Ref<NRHI::Buffer> debugUniformBuffer{};
        Ref<NRHI::Buffer> materialsUniformBuffer{};
        Ref<NRHI::Buffer> pointLightsUniformBuffer{};
    };
}
