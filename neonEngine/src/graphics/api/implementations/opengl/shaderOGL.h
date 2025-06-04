#pragma once
#include <glad/glad.h>

#include "graphics/api/shader.h"
#include "graphics/api/enums/shaderType.h"

namespace Neon
{
class ShaderOGL final : public Shader
{
public:
    explicit ShaderOGL(const std::unordered_map<ShaderType, std::vector<uint32_t>> &shadersSpirv);
    void compile() override;
    void dispose() override;

    void bind() const;
private:
    struct ShaderStage
    {
        std::string filePath;
        const char* source;
        uint32_t shaderType;
        uint32_t shaderHandle;
    };

    std::unordered_map<ShaderType, std::vector<uint32_t>> shadersSpirv;
    std::vector<GLuint> shaderHandles;
    GLuint handle{};
};
}
