#pragma once

namespace  Neon
{
    struct WindowOptions;

    class Window
    {
    public:
        explicit Window(WindowOptions options);
    };

    struct WindowOptions
    {
        const char* title{};
        int width = -1;
        int height = -1;
        bool vsync = false;
        bool fullscreen = true;
    };
}
