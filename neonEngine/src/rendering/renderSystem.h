#pragma once
#include "window.h"
#include "../core/system.h"

namespace Neon
{
    class RenderSystem final : public System
    {
    public:
        explicit RenderSystem(const WindowOptions &windowOptions);

        void startup() override;
        void shutdown() override;
        void render() override;
    private:
        WindowOptions windowOptions;
        Window window;
    };
}
