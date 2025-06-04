#pragma once
#include "shaderOGL.h"
#include "graphics/api/graphicsPipeline.h"
#include "graphics/api/descriptions/graphicsPipelineDescription.h"

namespace Neon
{
struct VertexAttributeOGL
{
    GLuint index;
    GLint size;
    GLenum type;
    GLsizei stride;
    const void *pointer;
};

class GraphicsPipelineOGL final : public GraphicsPipeline
{
public:
    explicit GraphicsPipelineOGL(GraphicsPipelineDescription &description);

    [[nodiscard]] std::vector<VertexAttributeOGL> getVertexAttributes() const;
    [[nodiscard]] Ref<ShaderOGL> getShader() const;

    GLuint vao{};
private:
    std::vector<VertexAttributeOGL> vertexAttributesOGL;
    Ref<ShaderOGL> shader;
    GraphicsPipelineDescription description;
};
}
