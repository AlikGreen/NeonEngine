#pragma once
#include <d3d11.h>
#include <dxgi.h>
#include <memory>

#include "window.h"
#include "../core/system.h"
#include "nvrhi/nvrhi.h"
#define GLFW_EXPOSE_NATIVE_WIN32
#define GLFW_EXPOSE_NATIVE_WGL
#include <windows.h>
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

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
        GLFWwindow* window = nullptr;
        IDXGISwapChain* swapChain = nullptr;
        ID3D11Device* device = nullptr;
        ID3D11DeviceContext* context = nullptr;
        nvrhi::DeviceHandle renderDevice;

        WindowOptions windowOptions;
        // std::unique_ptr<Window> window{};
    };
}
