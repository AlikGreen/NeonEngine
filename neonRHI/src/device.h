#pragma once
#include <string>

#include "commandList.h"
#include "graphicsPipeline.h"
#include "shader.h"

#include "descriptions/graphicsPipelineDescription.h"

#include "buffer.h"
#include "texture.h"
#include "descriptions/samplerDescription.h"
#include "util/memory.h"
#include "descriptions/textureDescription.h"

namespace NRHI
{
class Device
{
public:
    virtual ~Device() = default;

    virtual Ref<GraphicsPipeline> createGraphicsPipeline(GraphicsPipelineDescription graphicsPipelineDescription) = 0;
    virtual Ref<CommandList> createCommandList() = 0;

    virtual Ref<Texture> createTexture(TextureDescription textureDescription) = 0;
    virtual Ref<Sampler> createSampler(SamplerDescription samplerDescription) = 0;

    Ref<Shader> createShaderFromSource(const std::string &source, const std::string &filepath = "");

    virtual Ref<Buffer> createIndexBuffer() = 0;
    virtual Ref<Buffer> createUniformBuffer() = 0;
    virtual Ref<Buffer> createVertexBuffer() = 0;
    virtual void submit(Ref<CommandList> commandList) = 0;
    virtual void swapBuffers() = 0;

    virtual Ref<FrameBuffer> getSwapChainFrameBuffer() = 0;
protected:
    virtual Ref<Shader> createShaderFromSpirvImpl(std::unordered_map<ShaderType, std::vector<uint32_t>> spirv) = 0;
};
}
