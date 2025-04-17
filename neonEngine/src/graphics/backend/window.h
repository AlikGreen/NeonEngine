#pragma once

#include <SDL3/SDL.h>

namespace  Neon
{
    struct WindowOptions
    {
        const char* title{};
        int width = -1;
        int height = -1;
        bool vsync = false;
        bool fullscreen = false;
        bool resizable = true;
    };

    class Window
    {
    public:
        explicit Window(WindowOptions options);

        void run();
        void close(bool deinitSDL = true);
        operator SDL_Window*() const;

    private:
        static bool glfwInitialized;

        WindowOptions options;
        SDL_Window* handle = nullptr;
    };
}
