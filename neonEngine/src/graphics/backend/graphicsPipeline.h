#pragma once
#include "depthState.h"
#include "RenderTargetsDescription.h"
#include "shader.h"
#include "vertexInputState.h"

namespace Neon
{
    enum class PrimitiveType
    {
        TriangleList,
        TriangleStrip,
        LineList,
        LineStrip,
        PointList
    };

    enum class FillMode
    {
        Fill,
        Line,
    };

    enum class CullMode
    {
        Back,
        Front,
        None,
    };

    struct GraphicsPipelineDescription
    {
        Shader* shader = nullptr;
        PrimitiveType primitiveType = PrimitiveType::TriangleList;
        FillMode fillMode = FillMode::Fill;
        CullMode cullMode = CullMode::None;
        VertexInputState vertexInputState{};
        DepthState depthState{};
        RenderTargetsDescription targetsDescription{};
    };

    class GraphicsPipeline
    {
    public:
        explicit GraphicsPipeline(GraphicsPipelineDescription description);

        operator SDL_GPUGraphicsPipeline*() const;
        [[nodiscard]] SDL_GPUGraphicsPipeline* getHandle() const;
    private:
        static SDL_GPUPrimitiveType primitiveTypeToSDL(PrimitiveType type);
        static SDL_GPUFillMode fillModeToSDL(FillMode mode);
        static SDL_GPUCullMode cullModeToSDL(CullMode mode);

        SDL_GPUGraphicsPipeline* handle;
    };
}
