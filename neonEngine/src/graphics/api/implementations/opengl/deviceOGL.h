#pragma once
#include "graphics/api/device.h"

namespace Neon
{
class WindowOGL;
class DeviceOGL final : public Device
{
public:
    explicit DeviceOGL(WindowOGL* window);

    Ref<GraphicsPipeline> createGraphicsPipeline(GraphicsPipelineDescription graphicsPipelineDescription) override;
    Ref<CommandList> createCommandList() override;

    Ref<Buffer> createIndexBuffer() override;
    Ref<Buffer> createUniformBuffer() override;
    Ref<Buffer> createVertexBuffer() override;

    void submit(Ref<CommandList> commandList) override;
    void swapBuffers() override;

    Ref<FrameBuffer> getSwapChainFrameBuffer() override;
protected:
    Ref<Texture2D> createTexture2DImpl(uint32_t width, uint32_t height, TextureUsage usage, TextureFormat format, uint8_t* data) override;
    Ref<Shader> createShaderFromSpirvImpl(std::unordered_map<ShaderType, std::vector<uint32_t>> shadersSpirv) override;
private:
    WindowOGL* window;
};
}
