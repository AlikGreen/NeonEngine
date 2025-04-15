#include "renderSystem.h"



#include "messageCallback.h"
#include "../neonEngine.h"
#include "nvrhi/d3d11.h"

namespace Neon
{
    RenderSystem::RenderSystem(const WindowOptions &windowOptions)
    {
        this->windowOptions = windowOptions;
    }

    void RenderSystem::startup()
    {
        if (!glfwInit())
            return;

        // Ensure GLFW does not create an OpenGL context.
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

        // Create the window.
        window = glfwCreateWindow(1280, 720, "RenderSystem Window", nullptr, nullptr);
        if (!window) {
            glfwTerminate();
            return;
        }

        // Obtain the native window handle (HWND) for Direct3D initialization.
        HWND hwnd = glfwGetWin32Window(window);

        // Setup the swap chain description.
        DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
        swapChainDesc.BufferCount = 1;
        swapChainDesc.BufferDesc.Width = 1280;
        swapChainDesc.BufferDesc.Height = 720;
        swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        swapChainDesc.OutputWindow = hwnd;
        swapChainDesc.SampleDesc.Count = 1;
        swapChainDesc.Windowed = TRUE;

        // Create the Direct3D 11 device, device context, and swap chain.
        D3D_FEATURE_LEVEL featureLevels[] = { D3D_FEATURE_LEVEL_11_0 };
        D3D_FEATURE_LEVEL obtainedFeatureLevel;
        HRESULT hr = D3D11CreateDeviceAndSwapChain(
            nullptr,
            D3D_DRIVER_TYPE_HARDWARE,
            nullptr,
            0,
            featureLevels,
            1,
            D3D11_SDK_VERSION,
            &swapChainDesc,
            &swapChain,
            &device,
            &obtainedFeatureLevel,
            &context
        );
        if (FAILED(hr)) {
            glfwTerminate();
            return;
        }

        // Create an NVRHI device with the D3D11 device.
        nvrhi::d3d11::DeviceDesc nvrhiDesc = {};
        nvrhiDesc.context = context;
        renderDevice = nvrhi::d3d11::createDevice(nvrhiDesc);
    }

    void RenderSystem::render()
    {
        glfwPollEvents();
        if (glfwWindowShouldClose(window))
        {
            Engine::getInstance()->exit();
        }

        // Place your rendering code here.
        // For instance, you could clear the render target and issue drawing commands via renderDevice.

        // Present the swap chain.
        if (swapChain)
            swapChain->Present(1, 0);
    }

    void RenderSystem::shutdown()
    {
        if (swapChain) { swapChain->Release(); swapChain = nullptr; }
        if (context) { context->Release(); context = nullptr; }
        if (device) { device->Release(); device = nullptr; }

        if (window) {
            glfwDestroyWindow(window);
            window = nullptr;
        }
        glfwTerminate();
    }
}
