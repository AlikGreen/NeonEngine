#include "window.h"

#include <iostream>
#include <ostream>
#include <stdexcept>

namespace  Neon
{
    bool Window::glfwInitialized = false;

    Window::Window(WindowOptions options)
    {
        this->options = options;
        if (!glfwInitialized && !SDL_Init(SDL_INIT_VIDEO))
            throw std::runtime_error("Failed to initialize SDL");

        glfwInitialized = true;
    }

    void Window::run()
    {
        SDL_WindowFlags windowFlags = SDL_WINDOW_HIDDEN;
        if(options.resizable) windowFlags |= SDL_WINDOW_RESIZABLE;
        if(options.fullscreen) windowFlags |= SDL_WINDOW_FULLSCREEN;

        int width = options.width;
        int height = options.height;


        int num;
        SDL_DisplayID *displays = SDL_GetDisplays(&num);
        if(num < 1)
            throw std::runtime_error("Failed to retrieve displays");

        const SDL_DisplayMode *dm = SDL_GetCurrentDisplayMode(displays[0]);
        if (!dm)
        {
            SDL_Log("Couldn't get current display mode: %s", SDL_GetError());
            return;
        }

        if(width <= 0)
            width = static_cast<int>(dm->w*0.75);

        if(height <= 0)
            height = static_cast<int>(dm->h*0.75);

        handle = SDL_CreateWindow(options.title, width, height, windowFlags);
        if (!handle)
            throw std::runtime_error("Failed to create SDL window");

        SDL_ShowWindow(handle);
    }

    void Window::close(bool deinitSDL)
    {
        if(handle)
            SDL_DestroyWindow(handle);

        if(deinitSDL) SDL_Quit();
    }

    Window::operator SDL_Window*() const
    {
        return handle;
    }
}
