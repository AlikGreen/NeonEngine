# 0 "C:/Users/alikg/CLionProjects/neonEngine/neonEngine/src/rendering/window.cpp"
# 1 "C:\\Users\\alikg\\CLionProjects\\neonEngine\\sandboxApp\\cmake-build-debug//"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "C:/Users/alikg/CLionProjects/neonEngine/neonEngine/src/rendering/window.cpp"
# 1 "C:/Users/alikg/CLionProjects/neonEngine/neonEngine/src/rendering/window.h" 1
       

namespace Neon
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
# 2 "C:/Users/alikg/CLionProjects/neonEngine/neonEngine/src/rendering/window.cpp" 2

namespace Neon
{
    Window::Window(WindowOptions options)
    {

    }
}
