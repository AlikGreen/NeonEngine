#pragma once

#include "../core/system.h"
#include "backend/graphicsPipeline.h"
#include "backend/physicalDevice.h"
#include "backend/window.h"

namespace Neon
{
    struct MeshRenderer;

    class RenderSystem final : public System
    {
    public:
        explicit RenderSystem(const WindowOptions &windowOptions);

        void preStartup() override;
        void shutdown() override;
        void render() override;

        [[nodiscard]] PhysicalDevice* getDevice() const;
        [[nodiscard]] Window* getWindow() const;
    private:
        static void renderMesh(const MeshRenderer& meshRenderer, RenderPass renderPass, const CommandBuffer &commandBuffer);

        Window* window = nullptr;
        PhysicalDevice* physicalDevice = nullptr;
        GraphicsPipeline* pipeline = nullptr;
        Texture* depthTexture = nullptr;
    };
}
