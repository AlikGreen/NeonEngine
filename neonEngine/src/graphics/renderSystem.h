#pragma once

#include "core/system.h"
#include "api/device.h"
#include "api/window.h"

namespace Neon
{
    struct MeshRenderer;

    class RenderSystem final : public System
    {
    public:
        explicit RenderSystem(const WindowCreationOptions &windowOptions);

        void preStartup() override;
        void shutdown() override;
        void render() override;

        [[nodiscard]] Ref<Device> getDevice() const;
        [[nodiscard]] Ref<Window> getWindow() const;
    private:
        void renderMesh(const MeshRenderer& meshRenderer) const;

        Ref<Window> window{};
        Ref<Device> device{};
        Ref<GraphicsPipeline> pipeline{};
        Ref<Texture2D> depthTexture{};
        Ref<CommandList> commandList{};
        Ref<UniformBuffer> tintColorUniformBuffer{};
        Ref<UniformBuffer> mpvUniformBuffer{};
    };
}
