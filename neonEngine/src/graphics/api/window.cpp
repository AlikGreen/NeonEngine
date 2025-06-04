#include "window.h"

#include "implementations/opengl/windowOGL.h"

namespace Neon
{
    Ref<Window> Window::createWindow(const WindowCreationOptions& creationOptions, const BackendAPI backendApi)
    {
        switch (backendApi)
        {
            case BackendAPI::OpenGL:
                return makeRef<WindowOGL>(creationOptions);
        }

        return nullptr;
    }
}
