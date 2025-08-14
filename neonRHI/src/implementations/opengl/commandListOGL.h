#pragma once

#include <functional>
#include <vector>
#include "commandList.h"

namespace NRHI
{
    class GraphicsPipelineOGL;

    class CommandListOGL final : public CommandList
    {
    public:
        CommandListOGL() = default;

        void begin() override;

        void setUniformBuffer(std::string_view name, const Ref<Buffer>& buffer) override;
        void setTexture(      std::string_view name, uint32_t offset, const Ref<Texture>& texture) override;
        void setSampler(      std::string_view name, uint32_t offset, const Ref<Sampler>& sampler) override;

        void setPipeline(Ref<GraphicsPipeline> pipeline) override;
        void setFrameBuffer(Ref<FrameBuffer> frameBuffer) override;

        void setVertexBuffer(uint32_t index, Ref<Buffer> vertexBuffer) override;
        void setIndexBuffer(Ref<Buffer> indexBuffer, IndexFormat indexFormat) override;

        void clearColorTarget(uint32_t target, glm::vec4 color) override;
        void clearDepthStencil(float value) override;

        void updateTexture(const Ref<Texture>& texture, const void* data) override;
        void reserveBuffer(const Ref<Buffer>& buffer, size_t size) override;

        void executeCommands();
    protected:
        void drawImpl(uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) override;
        void drawIndexedImpl(uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int vertexOffset, uint32_t firstInstance) override;
        void updateBufferImpl(const Ref<Buffer>& buffer, void* data, uint32_t size) override;

    private:
        std::vector<std::function<void()>> commands{};
        GraphicsPipelineOGL* pipeline{};

        [[nodiscard]] GraphicsPipelineOGL* getPipeline() const;
    };
}