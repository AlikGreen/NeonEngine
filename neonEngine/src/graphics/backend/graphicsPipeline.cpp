#include "graphicsPipeline.h"

#include "../renderSystem.h"
#include "../../neonEngine.h"

namespace Neon
{
    GraphicsPipeline::GraphicsPipeline(GraphicsPipelineDescription description)
    {
        SDL_GPUVertexInputState vertexInputState{};
        std::vector vertexAttributes = description.vertexInputState.getVertexAttributes();
        vertexInputState.vertex_attributes = vertexAttributes.data();
        vertexInputState.num_vertex_attributes = vertexAttributes.size();
        std::vector vertexBuffers = description.vertexInputState.getVertexBuffers();
        vertexInputState.vertex_buffer_descriptions = vertexBuffers.data();
        vertexInputState.num_vertex_buffers = vertexBuffers.size();

        const auto* renderSystem = Engine::getInstance()->getSystem<RenderSystem>();

        SDL_GPUColorTargetDescription colorTargetDesc{};
        colorTargetDesc.format = SDL_GetGPUSwapchainTextureFormat(*renderSystem->getDevice(), *renderSystem->getWindow());
        const std::vector colorTargets = {colorTargetDesc};

        SDL_GPUGraphicsPipelineCreateInfo pipelineDesc{};
        pipelineDesc.vertex_shader = description.shader->getVertexShader();
        pipelineDesc.fragment_shader = description.shader->getFragmentShader();
        pipelineDesc.primitive_type = primitiveTypeToSDL(description.primitiveType);
        pipelineDesc.rasterizer_state.fill_mode = fillModeToSDL(description.fillMode);
        pipelineDesc.rasterizer_state.cull_mode = cullModeToSDL(description.cullMode);

        pipelineDesc.target_info.color_target_descriptions = colorTargets.data();
        pipelineDesc.target_info.num_color_targets = colorTargets.size();

        pipelineDesc.vertex_input_state = vertexInputState;

        handle = SDL_CreateGPUGraphicsPipeline(*renderSystem->getDevice(), &pipelineDesc);
        if(!handle)
            throw std::runtime_error("Failed to create graphics pipeline");
    }

    GraphicsPipeline::operator SDL_GPUGraphicsPipeline*() const
    {
        return handle;
    }

    SDL_GPUGraphicsPipeline * GraphicsPipeline::getHandle() const
    {
        return handle;
    }

    SDL_GPUPrimitiveType GraphicsPipeline::primitiveTypeToSDL(const PrimitiveType type)
    {
        switch (type)
        {
            case PrimitiveType::TriangleList: return SDL_GPU_PRIMITIVETYPE_TRIANGLELIST;
            case PrimitiveType::TriangleStrip: return SDL_GPU_PRIMITIVETYPE_TRIANGLESTRIP;
            case PrimitiveType::LineList: return SDL_GPU_PRIMITIVETYPE_LINELIST;
            case PrimitiveType::LineStrip: return SDL_GPU_PRIMITIVETYPE_LINESTRIP;
            case PrimitiveType::PointList: return SDL_GPU_PRIMITIVETYPE_POINTLIST;
            default: throw std::invalid_argument("Unknown PrimitiveType");
        }
    }

    SDL_GPUFillMode GraphicsPipeline::fillModeToSDL(FillMode mode)
    {
        switch (mode)
        {
            case FillMode::Fill: return SDL_GPU_FILLMODE_FILL;
            case FillMode::Line: return SDL_GPU_FILLMODE_LINE;
            default: throw std::invalid_argument("Unknown FillMode");
        }
    }

    SDL_GPUCullMode GraphicsPipeline::cullModeToSDL(CullMode mode)
    {
        switch (mode)
        {
            case CullMode::Front: return SDL_GPU_CULLMODE_FRONT;
            case CullMode::Back: return SDL_GPU_CULLMODE_BACK;
            case CullMode::None: return SDL_GPU_CULLMODE_NONE;
            default: throw std::invalid_argument("Unknown CullMode");
        }
    }
}
