#include "window.h"

#include "implementations/opengl/windowOGL.h"

namespace NRHI
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
