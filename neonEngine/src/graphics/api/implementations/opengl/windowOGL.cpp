#include "windowOGL.h"

#include <glad/glad.h>
#include <SDL3/SDL.h>

#include "convertOGL.h"
#include "deviceOGL.h"
#include "core/engine.h"
#include "core/eventManager.h"
#include "debug/assert.h"
#include "debug/logger.h"
#include "graphics/events/QuitEvent.h"
#include "graphics/events/windowResizeEvent.h"
#include "input/events/keyDownEvent.h"
#include "input/events/keyUpEvent.h"
#include "input/events/mouseButtonDownEvent.h"
#include "input/events/mouseButtonUpEvent.h"
#include "input/events/mouseMoveEvent.h"

namespace Neon
{
    WindowOGL::WindowOGL(const WindowCreationOptions &creationOptions) : creationOptions(creationOptions) { }

    Ref<Device> WindowOGL::createDevice()
    {
        return makeRef<DeviceOGL>(this);
    }

    void WindowOGL::run()
    {
        Assert::check(SDL_Init(SDL_INIT_VIDEO), "Failed to initialize SDL video subsystem");

        SDL_WindowFlags windowFlags = SDL_WINDOW_HIDDEN | SDL_WINDOW_OPENGL;
        if(creationOptions.resizable) windowFlags |= SDL_WINDOW_RESIZABLE;
        if(creationOptions.fullscreen) windowFlags |= SDL_WINDOW_FULLSCREEN;

        int width = creationOptions.width;
        int height = creationOptions.height;

        int displaysCount;
        const SDL_DisplayID *displays = SDL_GetDisplays(&displaysCount);

        Assert::check(displaysCount >= 1, "Failed to retrieve displays");

        const SDL_DisplayMode *dm = SDL_GetCurrentDisplayMode(displays[0]);
        Assert::check(dm != nullptr, "Couldn't get current display mode");

        if(width <= 0)
            width = static_cast<int>(dm->w*0.75);

        if(height <= 0)
            height = static_cast<int>(dm->h*0.75);

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

        handle = SDL_CreateWindow(creationOptions.title, width, height, windowFlags);
        Assert::check(handle != nullptr, "Failed to create SDL window");

        SDL_ShowWindow(handle);
        SDL_StartTextInput(handle);

        SDL_GL_CreateContext(handle);

        Assert::check(gladLoadGLLoader(reinterpret_cast<GLADloadproc>(SDL_GL_GetProcAddress)), "Failed to initialize GLAD");

        glViewport(0, 0, width, height);
    }

    void WindowOGL::close()
    {
        if(handle)
            SDL_DestroyWindow(handle);

        SDL_Quit();
    }

    void WindowOGL::pollEvents()
    {
        EventManager* eventManager = Engine::getEventManager();
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_EVENT_QUIT:
                    eventManager->queueEvent(new QuitEvent());
                    break;
                case SDL_EVENT_KEY_DOWN:
                    eventManager->queueEvent(new KeyDownEvent(ConvertOGL::keyCodeFromSDL(event.key.key), ConvertOGL::keyModFromSDL(event.key.mod)));
                    break;
                case SDL_EVENT_KEY_UP:
                    eventManager->queueEvent(new KeyUpEvent(ConvertOGL::keyCodeFromSDL(event.key.key), ConvertOGL::keyModFromSDL(event.key.mod)));
                    break;
                case SDL_EVENT_MOUSE_MOTION:
                    eventManager->queueEvent(new MouseMoveEvent(event.motion.x, event.motion.y));
                    break;
                case SDL_EVENT_MOUSE_BUTTON_DOWN:
                    eventManager->queueEvent(new MouseButtonDownEvent(ConvertOGL::mouseButtonFromSDL(event.button.button)));
                    break;
                case SDL_EVENT_MOUSE_BUTTON_UP:
                    eventManager->queueEvent(new MouseButtonUpEvent(ConvertOGL::mouseButtonFromSDL(event.button.button)));
                    break;
                case SDL_EVENT_WINDOW_RESIZED:
                    eventManager->queueEvent(new WindowResizeEvent(event.window.data1, event.window.data2));
                    break;
                default:
                    break;
            }
        }
    }

    uint32_t WindowOGL::getWidth()
    {
        return getSize().x;
    }

    uint32_t WindowOGL::getHeight()
    {
        return getSize().y;
    }

    glm::ivec2 WindowOGL::getSize()
    {
        glm::ivec2 size;
        SDL_GetWindowSize(handle, &size.x, &size.y);
        return size;
    }

    void WindowOGL::setWidth(const uint32_t width)
    {
        SDL_SetWindowSize(handle, static_cast<int>(width), static_cast<int>(getHeight()));
    }

    void WindowOGL::setHeight(const uint32_t height)
    {
        SDL_SetWindowSize(handle, static_cast<int>(getWidth()), static_cast<int>(height));
    }

    void WindowOGL::setSize(const glm::ivec2 size)
    {
        SDL_SetWindowSize(handle, size.x, size.y);
    }

    std::string WindowOGL::getTitle()
    {
        return SDL_GetWindowTitle(handle);
    }

    void WindowOGL::setTitle(const std::string title)
    {
        SDL_SetWindowTitle(handle, title.c_str());
    }

    void WindowOGL::swapBuffers() const
    {
        SDL_GL_SwapWindow(handle);
    }
}
