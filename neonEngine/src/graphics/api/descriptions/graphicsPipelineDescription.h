#pragma once
#include "graphics/api/shader.h"
#include "vertexInputState.h"

#include "graphics/api/enums/primitiveType.h"
#include "graphics/api/enums/fillMode.h"
#include "graphics/api/enums/cullMode.h"

#include "depthState.h"
#include "renderTargetsDescription.h"

namespace Neon
{
    struct GraphicsPipelineDescription
    {
        Ref<Shader> shader = nullptr;
        PrimitiveType primitiveType = PrimitiveType::TriangleList;
        FillMode fillMode = FillMode::Fill;
        CullMode cullMode = CullMode::None;
        VertexInputState vertexInputState{};
        DepthState depthState{};
        RenderTargetsDescription targetsDescription{};
    };
}
