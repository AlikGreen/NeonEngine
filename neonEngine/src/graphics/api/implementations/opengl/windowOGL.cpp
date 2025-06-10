#include "windowOGL.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

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
    void WindowOGL::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        EventManager& eventManager = Engine::getEventManager();

        if (action == GLFW_PRESS || action == GLFW_REPEAT)
            eventManager.queueEvent(new KeyDownEvent(ConvertOGL::keyCodeFromGLFW(key), ConvertOGL::keyModFromGLFW(mods)));
        else if (action == GLFW_RELEASE)
            eventManager.queueEvent(new KeyUpEvent(ConvertOGL::keyCodeFromGLFW(key), ConvertOGL::keyModFromGLFW(mods)));

    }

    void WindowOGL::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
    {
        EventManager& eventManager = Engine::getEventManager();

        if (action == GLFW_PRESS)
            eventManager.queueEvent(new MouseButtonDownEvent(ConvertOGL::mouseButtonFromGLFW(button)));
        else if (action == GLFW_RELEASE)
            eventManager.queueEvent(new MouseButtonUpEvent(ConvertOGL::mouseButtonFromGLFW(button)));
    }

    void WindowOGL::cursorPosCallback(GLFWwindow* window, const double xPos, const double yPos)
    {
        EventManager& eventManager = Engine::getEventManager();
        eventManager.queueEvent(new MouseMoveEvent(static_cast<float>(xPos), static_cast<float>(yPos)));
    }

    void WindowOGL::windowSizeCallback(GLFWwindow* window, const int width, const int height)
    {
        EventManager& eventManager = Engine::getEventManager();
        eventManager.queueEvent(new WindowResizeEvent(width, height));
        glViewport(0, 0, width, height);
    }

    void WindowOGL::windowCloseCallback(GLFWwindow* window)
    {
        EventManager& eventManager = Engine::getEventManager();
        eventManager.queueEvent(new QuitEvent());
    }

    WindowOGL::WindowOGL(const WindowCreationOptions &creationOptions) : creationOptions(creationOptions) { }

    Ref<Device> WindowOGL::createDevice()
    {
        return makeRef<DeviceOGL>(this);
    }

    void WindowOGL::run()
    {
        Assert::check(glfwInit(), "Failed to initialize GLFW");

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        glfwWindowHint(GLFW_RESIZABLE, creationOptions.resizable ? GLFW_TRUE : GLFW_FALSE);

        int width = creationOptions.width;
        int height = creationOptions.height;

        GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
        Assert::check(primaryMonitor != nullptr, "Failed to get primary monitor");

        const GLFWvidmode* mode = glfwGetVideoMode(primaryMonitor);
        Assert::check(mode != nullptr, "Couldn't get video mode");

        if(width <= 0)
            width = static_cast<int>(mode->width * 0.75);

        if(height <= 0)
            height = static_cast<int>(mode->height * 0.75);

        GLFWmonitor* monitor = creationOptions.fullscreen ? primaryMonitor : nullptr;
        handle = glfwCreateWindow(width, height, creationOptions.title, monitor, nullptr);
        Assert::check(handle != nullptr, "Failed to create GLFW window");

        glfwSetWindowUserPointer(handle, this);

        glfwSetKeyCallback(handle, keyCallback);
        glfwSetMouseButtonCallback(handle, mouseButtonCallback);
        glfwSetCursorPosCallback(handle, cursorPosCallback);
        glfwSetWindowSizeCallback(handle, windowSizeCallback);
        glfwSetWindowCloseCallback(handle, windowCloseCallback);

        glfwMakeContextCurrent(handle);

        Assert::check(gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)), "Failed to initialize GLAD");

        glViewport(0, 0, width, height);

        if(creationOptions.vsync)
            glfwSwapInterval(1);
        else
            glfwSwapInterval(0);
    }

    void WindowOGL::close()
    {
        if(handle)
            {
            glfwDestroyWindow(handle);
            handle = nullptr;
        }
        glfwTerminate();
    }

    void WindowOGL::pollEvents()
    {
        glfwPollEvents();
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
        glfwGetWindowSize(handle, &size.x, &size.y);
        return size;
    }

    void WindowOGL::setWidth(const uint32_t width)
    {
        glfwSetWindowSize(handle, static_cast<int>(width), static_cast<int>(getHeight()));
    }

    void WindowOGL::setHeight(const uint32_t height)
    {
        glfwSetWindowSize(handle, static_cast<int>(getWidth()), static_cast<int>(height));
    }

    void WindowOGL::setSize(const glm::ivec2 size)
    {
        glfwSetWindowSize(handle, size.x, size.y);
    }

    std::string WindowOGL::getTitle()
    {
        return glfwGetWindowTitle(handle);
    }

    void WindowOGL::setTitle(const std::string title)
    {
        glfwSetWindowTitle(handle, title.c_str());
    }

    void WindowOGL::swapBuffers() const
    {
        glfwSwapBuffers(handle);
    }

    void WindowOGL::setCursorLocked(const bool locked)
    {
        cursorLocked = locked;
        updateCursorState();
    }

    void WindowOGL::setCursorVisible(const bool visible)
    {
        cursorVisible = visible;
        updateCursorState();
    }

    void WindowOGL::updateCursorState() const
    {
        if (cursorLocked && !cursorVisible)
        {
            glfwSetInputMode(handle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        } else if (cursorLocked && cursorVisible)
        {
            glfwSetInputMode(handle, GLFW_CURSOR, GLFW_CURSOR_CAPTURED);
        } else if (!cursorVisible)
        {
            glfwSetInputMode(handle, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
        } else
        {
            glfwSetInputMode(handle, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
    }
}