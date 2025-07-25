#include "commandListOGL.h"

#include "frameBufferOGL.h"
#include "graphicsPipelineOGL.h"

#include <cstring>

#include "bufferOGL.h"
#include "debug/assert.h"

namespace Neon
{
    void CommandListOGL::executeCommands()
    {
        for (const auto& command: commands)
        {
            command();
        }
    }

    void CommandListOGL::begin()
    {
        commands.clear();
    }

    void CommandListOGL::setFrameBuffer(const Ref<FrameBuffer> frameBuffer)
    {
        commands.emplace_back([frameBuffer]
        {
            dynamic_cast<FrameBufferOGL*>(frameBuffer.get())->bind();
        });
    }

    void CommandListOGL::clearColorTarget(const uint32_t target, const glm::vec4 color)
    {
        commands.emplace_back([target, color]
        {
            glClearColor(color.x, color.y, color.z, color.w);
            const float clearColor[4] = {color.r, color.g, color.b, color.a};
            glClearBufferfv(GL_COLOR, static_cast<int>(target), clearColor);
        });
    }

    void CommandListOGL::clearDepthStencil(const float value)
    {
        commands.emplace_back([value]
        {
            glClearDepth(value);
            glClear(GL_DEPTH_BUFFER_BIT);
        });
    }

    void CommandListOGL::setVertexBuffer(const uint32_t index, const Ref<Buffer> vertexBuffer)
    {
        commands.emplace_back([this, vertexBuffer]
        {
            const auto* oglVertexBuffer = dynamic_cast<BufferOGL*>(vertexBuffer.get());
            Assert::check(oglVertexBuffer->getTarget() == GL_ARRAY_BUFFER, "Buffer being set as Vertex Buffer was not created as a Vertex Buffer");
            oglVertexBuffer->bind();

            const auto& attributes = pipeline->getVertexAttributes();
            for (const auto& attr : attributes)
            {
                if (attr.type == GL_INT || attr.type == GL_UNSIGNED_INT)
                {
                    glVertexAttribIPointer(attr.index, attr.size, attr.type, attr.stride, attr.pointer);
                } else
                {
                    glVertexAttribPointer(attr.index, attr.size, attr.type, GL_FALSE, attr.stride, attr.pointer);
                }
                glEnableVertexAttribArray(attr.index);
            }
        });
    }

    void CommandListOGL::setIndexBuffer(const Ref<Buffer> indexBuffer, const IndexFormat indexFormat)
    {
        commands.emplace_back([indexBuffer]
        {
            const auto* indexBufferOGL = dynamic_cast<BufferOGL*>(indexBuffer.get());
            Assert::check(indexBufferOGL->getTarget() == GL_ELEMENT_ARRAY_BUFFER, "Buffer being set as Index Buffer was not created as an Index Buffer");
            indexBufferOGL->bind();
        });
    }

    void CommandListOGL::setUniformBuffer(uint32_t slot, ShaderType shaderType, const Ref<Buffer> &buffer)
    {
        commands.emplace_back([buffer, slot]
        {
            const auto* uniformBufferOGL = dynamic_cast<BufferOGL*>(buffer.get());
            Assert::check(uniformBufferOGL->getTarget() == GL_UNIFORM_BUFFER, "Buffer being set as Uniform Buffer was not created as an Uniform Buffer");
            uniformBufferOGL->bindBase(slot);
        });
    }

    void CommandListOGL::setPipeline(const Ref<GraphicsPipeline> pipeline)
    {
        commands.emplace_back([this, pipeline]
        {
            this->pipeline = dynamic_cast<GraphicsPipelineOGL*>(pipeline.get());
            this->pipeline->bind();
        });
    }

    void CommandListOGL::reserveBuffer(const Ref<Buffer> &buffer, size_t size)
    {
        commands.emplace_back([buffer, size]
        {
            auto* bufferOGL = dynamic_cast<BufferOGL*>(buffer.get());
            bufferOGL->reserveSpace(size);
        });
    }

    void CommandListOGL::drawImpl(const uint32_t vertexCount, const uint32_t instanceCount, const uint32_t firstVertex,
                                  const uint32_t firstInstance)
    {
        commands.emplace_back([vertexCount, instanceCount, firstVertex, firstInstance]
        {
            glDrawArraysInstancedBaseInstance(GL_TRIANGLES, static_cast<int>(firstVertex), static_cast<int>(vertexCount), static_cast<int>(instanceCount), firstInstance);
        });
    }

    void CommandListOGL::drawIndexedImpl(const uint32_t indexCount, const uint32_t instanceCount, const uint32_t firstIndex,
                                         const int vertexOffset, const uint32_t firstInstance)
    {
        commands.emplace_back([indexCount, instanceCount, firstIndex, vertexOffset, firstInstance]
        {
            glDrawElementsInstancedBaseVertexBaseInstance(GL_TRIANGLES, static_cast<int>(indexCount), GL_UNSIGNED_INT, reinterpret_cast<void *>(firstIndex), static_cast<int>(instanceCount), vertexOffset, firstInstance);
        });
    }

    void CommandListOGL::updateBufferImpl(const Ref<Buffer> &buffer, void *data, uint32_t size)
    {
        std::vector dataCopy(static_cast<uint8_t*>(data), static_cast<uint8_t*>(data) + size);

        auto* bufferOGL = dynamic_cast<BufferOGL*>(buffer.get());
        commands.emplace_back([bufferOGL, dataCopy = std::move(dataCopy), size]
        {
            bufferOGL->uploadData(dataCopy.data(), size);
        });
    }
}
