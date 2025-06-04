#pragma once
#include "commandList.h"
#include "graphicsPipeline.h"
#include "shader.h"
#include "textures/texture2D.h"
#include "descriptions/graphicsPipelineDescription.h"
#include "util/memory.h"

#include "enums/textureUsage.h"
#include "enums/textureFormat.h"

namespace Neon
{
class Device
{
public:
    virtual ~Device() = default;

    virtual Ref<GraphicsPipeline> createGraphicsPipeline(GraphicsPipelineDescription graphicsPipelineDescription) = 0;
    virtual Ref<CommandList> createCommandList() = 0;
    virtual Ref<IndexBuffer> createIndexBuffer(std::vector<uint32_t> data) = 0;

    Ref<Texture2D> createTexture2D(uint32_t width, uint32_t height, TextureUsage usage = TextureUsage::Sampler, TextureFormat format = TextureFormat::R8G8B8A8Unorm, uint8_t* data = nullptr);
    Ref<Shader> createShaderFromPath(const std::string &filepath);
    Ref<Shader> createShaderFromSource(const std::string &source, const std::string &filepath);

    template<typename T>
    Ref<UniformBuffer> createUniformBuffer(T& data)
    {
        return createUniformBufferImpl(&data, sizeof(T));
    }

    template<typename T>
    Ref<UniformBuffer> createUniformBuffer()
    {
        return createUniformBufferImpl(nullptr, sizeof(T));
    }

    template<typename T>
    Ref<VertexBuffer> createVertexBuffer(std::vector<T> data)
    {
        return createVertexBufferImpl(data.data(), data.size(), sizeof(T));
    }

    virtual void submitCommandList(Ref<CommandList> commandList) = 0;
    virtual void swapBuffers() = 0;

    virtual Ref<FrameBuffer> getSwapChainFrameBuffer() = 0;
protected:
    virtual Ref<Shader> createShaderFromSpirvImpl(std::unordered_map<ShaderType, std::vector<uint32_t>> spirv) = 0;
    virtual Ref<Texture2D> createTexture2DImpl(uint32_t width, uint32_t height, TextureUsage usage, TextureFormat format, uint8_t* data) = 0;
    virtual Ref<VertexBuffer> createVertexBufferImpl(void* data, uint32_t elementCount, uint32_t elementSize) = 0;
    virtual Ref<UniformBuffer> createUniformBufferImpl(void* data, uint32_t size) = 0;
};
}