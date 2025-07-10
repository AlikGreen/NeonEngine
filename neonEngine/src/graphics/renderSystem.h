#pragma once

#include "core/system.h"
#include "api/device.h"
#include "api/window.h"
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
        explicit RenderSystem(const WindowCreationOptions &windowOptions);

        void preStartup() override;
        void shutdown() override;
        void preUpdate() override;
        void render() override;

        [[nodiscard]] Ref<Device> getDevice() const;
        [[nodiscard]] Ref<Window> getWindow() const;
    private:
        void renderMesh(EntityID entity, const MeshRenderer& meshRenderer) const;

        Ref<Window> window{};
        Ref<Device> device{};

        Ref<GraphicsPipeline> pipeline{};
        Ref<Texture> depthTexture{};
        Ref<CommandList> commandList{};

        Ref<Buffer> cameraUniformBuffer{};
        Ref<Buffer> modelUniformBuffer{};
        Ref<Buffer> debugUniformBuffer{};
        Ref<Buffer> materialsUniformBuffer{};
        Ref<Buffer> pointLightsUniformBuffer{};
    };
}
