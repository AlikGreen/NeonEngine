#pragma once
#include <vector>
#include <SDL3/SDL.h>

#include "graphicsPipeline.h"

namespace Neon
{
class RenderPass
{
public:
    RenderPass() = delete;

    void bindPipeline(GraphicsPipeline* pipeline);
    void bindVertexBuffers(int slot, const std::vector<SDL_GPUBufferBinding> &vertexBufferBindings) const;
    void draw(int verticesCount, int instancesCount, int firstVertex = 0, int firstInstance = 0) const;
    void end() const;
private:
    friend class CommandBuffer;
    explicit RenderPass(SDL_GPURenderPass* handle);

    SDL_GPURenderPass* handle;
};
}
