#pragma once
#include <string>
#include <vector>

#include <SDL3/SDL.h>

#include "backendAPIEnum.h"
#include "shaderc/shaderc.hpp"

namespace Neon
{
class Shader
{
public:
    explicit Shader(const std::string &filePath);
    void compile();
    void dispose() const;


private:
    friend class GraphicsPipeline;

    struct ShaderData
    {
        std::string filePath;
        std::string source;
        shaderc_shader_kind shaderStage;
        SDL_GPUShaderFormat shaderFormat;
    };

    struct DescriptorCounts
    {
        uint32_t samplers          = 0;
        uint32_t uniformBuffers    = 0;
        uint32_t storageBuffers    = 0;
        uint32_t storageTextures   = 0;
    };

    static std::vector<uint32_t> compileShaderToSpirv(const std::string &source, shaderc_shader_kind kind, const std::string &debugFileName = "shader.glsl");
    static std::vector<uint8_t> compileShaderForBackend( std::vector<uint32_t> spirv, BackendAPI backend);
    static SDL_GPUShader* compileSDLShader(const ShaderData &shaderData);
    static DescriptorCounts reflectDescriptorCounts(const std::vector<uint32_t>& spirv);

    [[nodiscard]] SDL_GPUShader* getVertexShader() const;
    [[nodiscard]] SDL_GPUShader* getFragmentShader() const;

    SDL_GPUShader* vertexShader = nullptr;
    SDL_GPUShader* fragmentShader = nullptr;

    std::vector<ShaderData> shadersData;

    shaderc::Compiler compiler;
};
}
