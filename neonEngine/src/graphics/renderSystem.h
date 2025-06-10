#pragma once

#include "core/system.h"
#include "api/device.h"
#include "api/window.h"
#include "components/meshRenderer.h"
#include "components/pointLight.h"
#include "ecs/componentList.h"
#include "ecs/components/transformComponent.h"

namespace Neon
{
    struct CameraUniforms
    {
        glm::mat4 view;
        glm::mat4 proj;
    };

    struct ModelUniforms
    {
        glm::mat4 model;
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
        void renderMesh(const MeshRenderer& meshRenderer, const Transform& transform) const;

        Ref<Window> window{};
        Ref<Device> device{};

        Ref<GraphicsPipeline> pipeline{};
        Ref<Texture2D> depthTexture{};
        Ref<CommandList> commandList{};

        Ref<UniformBuffer> cameraUniformBuffer{};
        Ref<UniformBuffer> modelUniformBuffer{};
        Ref<UniformBuffer> debugUniformBuffer{};
        Ref<UniformBuffer> materialUniformBuffer{};
        Ref<UniformBuffer> pointLightsUniformBuffer{};
    };
}
