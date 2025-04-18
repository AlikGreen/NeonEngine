#pragma once
#include <string>
#include <vector>

#include <SDL3/SDL.h>

#include "shaderc/shaderc.hpp"

namespace Neon
{
class Shader
{
public:
    Shader(std::string filePath);
    void compile();

    SDL_GPUShader* vertexShader = nullptr;
    SDL_GPUShader* fragmentShader = nullptr;
private:
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

    static SDL_GPUShader* compileShader(const ShaderData &shaderData);
    static DescriptorCounts reflectDescriptorCounts(const std::vector<uint32_t>& spirvBytes);

    std::vector<ShaderData> shadersData;

    shaderc::Compiler compiler;
};
}
