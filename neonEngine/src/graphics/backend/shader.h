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

private:
    void createShader(std::string source, SDL_GPUShaderStage stage);

    void compile();

    std::vector<char> fragmentShaderCode;
    std::vector<char> vertexShaderCode;

    SDL_GPUShader* vertexShader = nullptr;
    SDL_GPUShader* fragmentShader = nullptr;

    shaderc::Compiler compiler;
};
}
