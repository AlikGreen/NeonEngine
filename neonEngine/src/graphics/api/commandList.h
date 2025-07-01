#pragma once
#include "frameBuffer.h"
#include "graphicsPipeline.h"
#include "buffer.h"
#include "enums/indexFormat.h"
#include "glm/glm.hpp"

namespace Neon
{
    enum class ShaderType;
}

namespace Neon
{
class CommandList
{
public:
    virtual ~CommandList() = default;

    virtual void begin() = 0;


    virtual void setFrameBuffer(Ref<FrameBuffer> frameBuffer) = 0;

    void draw(const uint32_t vertexCount, const uint32_t instanceCount = 1, const uint32_t firstVertex = 0, const uint32_t firstInstance = 0)
        { drawImpl(vertexCount, instanceCount, firstVertex, firstInstance); };
    void drawIndexed(const uint32_t indexCount, const uint32_t instanceCount = 1, const uint32_t firstIndex = 0, const int vertexOffset = 0, const uint32_t firstInstance = 0)
        { drawIndexedImpl(indexCount, instanceCount, firstIndex, vertexOffset, firstInstance); };

    virtual void clearColorTarget(uint32_t target, glm::vec4 color) = 0;
    virtual void clearDepthStencil(float value) = 0;

    virtual void setVertexBuffer(uint32_t index, Ref<Buffer> vertexBuffer) = 0;
    virtual void setIndexBuffer(Ref<Buffer> indexBuffer, IndexFormat indexFormat) = 0;
    virtual void setUniformBuffer(uint32_t slot, ShaderType shaderType, const Ref<Buffer>& buffer) = 0;

    virtual void setPipeline(Ref<GraphicsPipeline> pipeline) = 0;

    virtual void reserveBuffer(const Ref<Buffer>& buffer, size_t size) = 0;

    template<typename T>
    void updateBuffer(const Ref<Buffer>& buffer, T& data)
    {
        updateBufferImpl(buffer, &data, sizeof(T));
    }

    template<typename T>
    void updateBuffer(const Ref<Buffer>& buffer, std::vector<T> data)
    {
        updateBufferImpl(buffer, data.data(), sizeof(T)*data.size());
    }

    template<typename T>
    void updateBuffer(const Ref<Buffer>& buffer, T* data)
    {
        updateBufferImpl(buffer, data, sizeof(T));
    }
protected:
    virtual void drawImpl(uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) = 0;
    virtual void drawIndexedImpl(uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int vertexOffset, uint32_t firstInstance) = 0;
    virtual void updateBufferImpl(const Ref<Buffer>& buffer, void* data, uint32_t size) = 0;
};
}
