#pragma once
#include "shaderOGL.h"
#include "graphics/api/commandList.h"

namespace Neon
{
    class GraphicsPipelineOGL;
    class CommandListOGL final : public CommandList
    {
    public:
        CommandListOGL() = default;

        void begin() override;
        void setFrameBuffer(Ref<FrameBuffer> frameBuffer) override;

        void clearColorTarget(uint32_t target, glm::vec4 color) override;
        void clearDepthStencil(float value) override;
        void setVertexBuffer(uint32_t index, Ref<VertexBuffer> vertexBuffer) override;
        void setIndexBuffer(Ref<IndexBuffer> indexBuffer, IndexFormat indexFormat) override;
        void setUniformBuffer(uint32_t slot, ShaderType shaderType, const Ref<UniformBuffer>& buffer) override;

        void setPipeline(Ref<GraphicsPipeline> pipeline) override;

        void executeCommands();

        GraphicsPipelineOGL* pipeline{};
    protected:
        void drawImpl(uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) override;
        void drawIndexedImpl(uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int vertexOffset, uint32_t firstInstance) override;
        void updateBufferImpl(const Ref<Buffer> &buffer, void *data, uint32_t size) override;
    private:
        std::vector<std::function<void()>> commands{};
    };
}
