#include "graphicsPipelineOGL.h"

#include <utility>

#include "convertOGL.h"

namespace Neon
{
    GraphicsPipelineOGL::GraphicsPipelineOGL(GraphicsPipelineDescription &description) : description(description)
    {
        shader = std::dynamic_pointer_cast<ShaderOGL>(description.shader);

        uint32_t offset = 0;
        for (const auto& attr : description.vertexInputState.getVertexAttributes())
        {
            const GLenum glType = ConvertOGL::typeinfoToGL(attr.type);
            VertexAttributeOGL attrib =
            {
                attr.location,
                static_cast<int>(ConvertOGL::getComponentCount(attr.type)), glType,
                static_cast<int>(description.vertexInputState.getStride()),
                reinterpret_cast<const void*>(offset)
            };

            vertexAttributesOGL.push_back(attrib);

            offset += attr.size;
        }

        glGenVertexArrays(1, &vao);
    }

    std::vector<VertexAttributeOGL> GraphicsPipelineOGL::getVertexAttributes() const
    {
        return vertexAttributesOGL;
    }

    Ref<ShaderOGL> GraphicsPipelineOGL::getShader() const
    {
        return shader;
    }
}
