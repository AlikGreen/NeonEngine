#include "renderPass.h"

#include "graphicsPipeline.h"

namespace Neon
{
    void RenderPass::bindPipeline(GraphicsPipeline* pipeline)
    {
        SDL_BindGPUGraphicsPipeline(handle, *pipeline);
    }

    void RenderPass::bindVertexBuffers(const int slot, const std::vector<SDL_GPUBufferBinding> &vertexBufferBindings) const
    {
        SDL_BindGPUVertexBuffers(handle, slot, vertexBufferBindings.data(), vertexBufferBindings.size());
    }

    void RenderPass::draw(const int verticesCount, const int instancesCount, const int firstVertex, const int firstInstance) const
    {
        SDL_DrawGPUPrimitives(handle, verticesCount, instancesCount, firstVertex, firstInstance);
    }

    void RenderPass::end() const
    {
        SDL_EndGPURenderPass(handle);
    }

    RenderPass::RenderPass(SDL_GPURenderPass *handle) : handle(handle)
    {

    }
}
