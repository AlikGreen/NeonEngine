#pragma once

#include "window.h"
#include "SDL3/SDL.h"
#include "../core/system.h"


namespace Neon
{
    struct Vertex {
        float position[3];
        float texCoord[2];
    };

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
        SDL_Renderer* renderer = nullptr;
    };
}
