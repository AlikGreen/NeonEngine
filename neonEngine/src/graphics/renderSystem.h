#pragma once

#include "SDL3/SDL.h"
#include "../core/system.h"
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

        SDL_GPUDevice* getDevice();
    private:
        Window* window = nullptr;
        SDL_GPUDevice* device = nullptr;
        SDL_GPUGraphicsPipeline* pipeline = nullptr;
        SDL_GPUBuffer* vertexBuffer = nullptr;
    };
}
