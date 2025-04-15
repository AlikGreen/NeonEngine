#include "renderSystem.h"

namespace Neon
{
    RenderSystem::RenderSystem(const WindowOptions &windowOptions)
    {
        this->windowOptions = windowOptions;
    }

    void RenderSystem::startup()
    {
        window = Window(windowOptions);
    }

    void RenderSystem::shutdown()
    {

    }

    void RenderSystem::render()
    {

    }
}
