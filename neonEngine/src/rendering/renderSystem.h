#pragma once

#include "window.h"
#include "SDL3/SDL.h"
#include "../core/system.h"


namespace Neon
{
    class RenderSystem final : public System
    {
    public:
        explicit RenderSystem(const WindowOptions &windowOptions);

        void startup() override;
        void shutdown() override;
        void render() override;
    private:
        WindowOptions windowOptions;

        SDL_Window* window = nullptr;
        SDL_GPUDevice* device = nullptr;
        SDL_GPUGraphicsPipeline* pipeline = nullptr;
        SDL_GPUBuffer* vertexBuffer = nullptr;
    };
}
