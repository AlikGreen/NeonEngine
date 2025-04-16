#include "renderSystem.h"

#include <iostream>

#include "../neonEngine.h"

namespace Neon
{
    RenderSystem::RenderSystem(const WindowOptions &windowOptions)
    {
        this->windowOptions = windowOptions;
    }

    void RenderSystem::startup()
    {
        std::cout << "START Render" << std::endl;
        if (!SDL_Init(SDL_INIT_VIDEO))
        {
            printf("SDL_Init Error: %s\n", SDL_GetError());
            // If SDL_GetError() returns empty, try printing the return value
            printf("SDL_Init Return Code: %d\n", SDL_Init(SDL_INIT_VIDEO));
            return;
        }

        // Create the window (using SDL_WINDOW_OPENGL flag for GPU rendering)
        window = SDL_CreateWindow("SDL 3 Triangle Example", 800, 600,
                         SDL_WINDOW_RESIZABLE);
        if (!window) {
            SDL_Log("Failed to create window: %s", SDL_GetError());
            return;
        }

        // Create a hardware-accelerated renderer
        renderer = SDL_CreateRenderer(window, "vulkan");
        if (!renderer) {
            SDL_Log("Failed to create renderer: %s", SDL_GetError());
            return;
        }
    }

    void RenderSystem::render() {
        // Clear the screen with a black color
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Define three vertices for the triangle using SDL_Vertex.
        SDL_Vertex vertices[3];

        // Vertex 0 (Red)
        vertices[0].position.x = 400;
        vertices[0].position.y = 100;
        vertices[0].color = {255, 0, 0, 255};
        vertices[0].tex_coord.x = 0.0f;
        vertices[0].tex_coord.y = 0.0f;

        // Vertex 1 (Green)
        vertices[1].position.x = 100;
        vertices[1].position.y = 500;
        vertices[1].color = {0, 255, 0, 255};
        vertices[1].tex_coord.x = 0.0f;
        vertices[1].tex_coord.y = 0.0f;

        // Vertex 2 (Blue)
        vertices[2].position.x = 700;
        vertices[2].position.y = 500;
        vertices[2].color = {0, 0, 255, 255};
        vertices[2].tex_coord.x = 0.0f;
        vertices[2].tex_coord.y = 0.0f;

        // Render the triangle. Since we are not applying any texture, we pass NULL as texture.
        // SDL_RenderGeometry will treat consecutive vertices as a triangle.
        SDL_RenderGeometry(renderer, nullptr, vertices, 3, nullptr, 0);

        // Present the rendered frame on screen
        SDL_RenderPresent(renderer);
    }

    void RenderSystem::shutdown() {
        // Clean up renderer and window, then quit SDL
        if (renderer) {
            SDL_DestroyRenderer(renderer);
            renderer = nullptr;
        }

        if (window) {
            SDL_DestroyWindow(window);
            window = nullptr;
        }

        SDL_Quit();
    }
}
