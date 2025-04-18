#pragma once

#include "SDL3/SDL.h"
#include "../core/system.h"
#include "backend/backendAPIEnum.h"
#include "backend/graphicsPipeline.h"
#include "backend/physicalDevice.h"
#include "backend/window.h"


namespace Neon
{
    class RenderSystem final : public System
    {
    public:
        explicit RenderSystem(const WindowOptions &windowOptions);

        void startup() override;
        void shutdown() override;
        void render() override;

        [[nodiscard]] PhysicalDevice* getDevice() const;
        [[nodiscard]] Window* getWindow() const;
    private:
        Window* window = nullptr;
        PhysicalDevice* physicalDevice = nullptr;
        GraphicsPipeline* pipeline = nullptr;

        SDL_GPUBuffer* vertexBuffer = nullptr;

    };
}
