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

    Ref<Texture> createTexture(TextureDescription textureDescription) override;

    void submit(Ref<CommandList> commandList) override;
    void swapBuffers() override;

    Ref<FrameBuffer> getSwapChainFrameBuffer() override;
protected:
    Ref<Shader> createShaderFromSpirvImpl(std::unordered_map<ShaderType, std::vector<uint32_t>> shadersSpirv) override;
private:
    WindowOGL* window;
};
}
