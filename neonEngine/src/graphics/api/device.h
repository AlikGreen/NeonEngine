#pragma once
#include "commandList.h"
#include "graphicsPipeline.h"
#include "shader.h"
#include "textures/texture2D.h"
#include "descriptions/graphicsPipelineDescription.h"
#include "util/memory.h"

#include "enums/textureUsage.h"
#include "enums/textureFormat.h"

#include "buffer.h"

namespace Neon
{
class Device
{
public:
    virtual ~Device() = default;

    virtual Ref<GraphicsPipeline> createGraphicsPipeline(GraphicsPipelineDescription graphicsPipelineDescription) = 0;
    virtual Ref<CommandList> createCommandList() = 0;

    Ref<Texture2D> createTexture2D(uint32_t width, uint32_t height, TextureUsage usage = TextureUsage::Sampler, TextureFormat format = TextureFormat::R8G8B8A8Unorm, uint8_t* data = nullptr);

    Ref<Shader> createShaderFromSource(const std::string &source, const std::string &filepath = "");

    virtual Ref<Buffer> createIndexBuffer() = 0;
    virtual Ref<Buffer> createUniformBuffer() = 0;
    virtual Ref<Buffer> createVertexBuffer() = 0;
    virtual void submit(Ref<CommandList> commandList) = 0;
    virtual void swapBuffers() = 0;

    virtual Ref<FrameBuffer> getSwapChainFrameBuffer() = 0;
protected:
    virtual Ref<Shader> createShaderFromSpirvImpl(std::unordered_map<ShaderType, std::vector<uint32_t>> spirv) = 0;

    virtual Ref<Texture2D> createTexture2DImpl(uint32_t width, uint32_t height, TextureUsage usage, TextureFormat format, uint8_t* data) = 0;
};
}