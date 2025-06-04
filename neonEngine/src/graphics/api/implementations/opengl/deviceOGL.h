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
    Ref<IndexBuffer> createIndexBuffer(std::vector<uint32_t> data) override;

    void submitCommandList(Ref<CommandList> commandList) override;
    void swapBuffers() override;

    Ref<FrameBuffer> getSwapChainFrameBuffer() override;
protected:
    Ref<Texture2D> createTexture2DImpl(uint32_t width, uint32_t height, TextureUsage usage, TextureFormat format, uint8_t* data) override;
    Ref<VertexBuffer> createVertexBufferImpl(void* data, uint32_t elementCount, uint32_t elementSize) override;
    Ref<Shader> createShaderFromSpirvImpl(std::unordered_map<ShaderType, std::vector<uint32_t>> shadersSpirv) override;
    Ref<UniformBuffer> createUniformBufferImpl(void* data, uint32_t size) override;
private:
    WindowOGL* window;
};
}
