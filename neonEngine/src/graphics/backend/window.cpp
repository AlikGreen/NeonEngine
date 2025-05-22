#include "window.h"

#include <iostream>
#include <ostream>
#include <stdexcept>

#include "graphics/renderSystem.h"
#include "core/engine.h"
#include "input/keyCodes.h"
#include "input/events/keyDownEvent.h"
#include "input/events/keyUpEvent.h"
#include "input/events/mouseButtonDownEvent.h"
#include "input/events/mouseButtonUpEvent.h"
#include "input/events/textInputEvent.h"

namespace  Neon
{
    bool Window::glfwInitialized = false;

    Window::Window(const WindowOptions &options)
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
        SDL_StartTextInput(handle);
    }

    void Window::close(const bool deinitSDL) const
    {
        if(handle)
            SDL_DestroyWindow(handle);

        if(deinitSDL) SDL_Quit();
    }

    void Window::pollEvents()
    {
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_EVENT_QUIT:
                    Engine::quit();
                    break;
                case SDL_EVENT_KEY_DOWN:
                    Engine::getEventManager()->queueEvent(new KeyDownEvent(static_cast<KeyCode>(event.key.key), static_cast<KeyMod>(event.key.mod)));
                    break;
                case SDL_EVENT_KEY_UP:
                    Engine::getEventManager()->queueEvent(new KeyUpEvent(static_cast<KeyCode>(event.key.key), static_cast<KeyMod>(event.key.mod)));
                    break;
                case SDL_EVENT_MOUSE_BUTTON_DOWN:
                    Engine::getEventManager()->queueEvent(new MouseButtonDownEvent(static_cast<MouseButton>(event.button.button)));
                    break;
                case SDL_EVENT_MOUSE_BUTTON_UP:
                    Engine::getEventManager()->queueEvent(new MouseButtonUpEvent(static_cast<MouseButton>(event.button.button)));
                    break;
                case SDL_EVENT_TEXT_INPUT:
                    Engine::getEventManager()->queueEvent(new TextInputEvent(event.text.text));
                    break;
                default:
                    break;
            }
        }
    }

    int Window::getWidth() const
    {
        int width = 0;
        SDL_GetWindowSize(handle, &width, nullptr);
        return width;
    }

    int Window::getHeight() const
    {
        int height = 0;
        SDL_GetWindowSize(handle, nullptr, &height);
        return height;
    }


    Window::operator SDL_Window*() const
    {
        return handle;
    }

    SDL_Window * Window::getHandle() const
    {
        return handle;
    }
}
