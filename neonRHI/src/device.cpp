#include "device.h"

#include <util/file.h>
#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>

#include "util/memory.h"
#include "enums/shaderType.h"
#include "shaderc/shaderc.h"
#include "shaderc/shaderc.hpp"
#include "util/string.h"

namespace NRHI
{
    std::vector<uint32_t> compileToSpirv(const std::string& source_name,
                                        const ShaderType type,
                                        const std::string& source,
                                        const bool optimize = false)
    {
        const shaderc::Compiler compiler;
        shaderc::CompileOptions options;

        if (optimize) options.SetOptimizationLevel(shaderc_optimization_level_size);

        shaderc_shader_kind shaderKind = {};
        if (type == ShaderType::Vertex) shaderKind = shaderc_vertex_shader;
        else if (type == ShaderType::Fragment) shaderKind = shaderc_fragment_shader;
        else if (type == ShaderType::Compute) shaderKind = shaderc_compute_shader;

        const shaderc::SpvCompilationResult module = compiler.CompileGlslToSpv(source, shaderKind, source_name.c_str(), options);

        // Assert::check<std::string>(module.GetCompilationStatus() == shaderc_compilation_status_success, "Compilation Error:\n {}", module.GetErrorMessage());
        if(module.GetCompilationStatus() != shaderc_compilation_status_success)
        {
            std::printf("Compilation Error:\n %s", module.GetErrorMessage().c_str());
        }
        return {module.cbegin(), module.cend()};
    }

    Shader* Device::createShaderFromSource(const std::string &source, const std::string &filepath)
    {
        std::unordered_map<ShaderType, std::string> shaderSources;
        std::string common;

        std::istringstream stream(source);
        std::string line;
        std::string currentSection;
        std::string currentShaderType;
        bool inShaderSection = false;

        uint32_t shaderStartLine = 0;
        uint32_t currentLine = 0;

        while (std::getline(stream, line))
        {
            currentLine++;
            std::string trimmedLine = String::trim(line);

            if (trimmedLine.substr(0, 5) == "#type")
            {
                if (inShaderSection && !currentShaderType.empty())
                {
                    std::string shaderSource =  common +
                                                "#line "+std::to_string(shaderStartLine)+"\n"+
                                                currentSection;

                    shaderSource = String::trim(shaderSource);

                    if(currentShaderType == "vertex")
                        shaderSources[ShaderType::Vertex] = shaderSource;
                    else if(currentShaderType == "fragment")
                        shaderSources[ShaderType::Fragment] = shaderSource;
                    else if(currentShaderType == "compute")
                        shaderSources[ShaderType::Compute] = shaderSource;
                }

                shaderStartLine = currentLine+1;

                const size_t spacePos = trimmedLine.find_first_of(" \t", 5);
                if (spacePos != std::string::npos)
                {
                    currentShaderType = String::toLower(String::trim(trimmedLine.substr(spacePos + 1)));
                    currentSection.clear();
                    inShaderSection = true;
                }
            }
            else if (inShaderSection)
            {
                currentSection += line + "\n";
            }
            else
            {
                common += line + "\n";
            }
        }

        if (inShaderSection && !currentShaderType.empty())
        {
            std::string shaderSource =  common +
                                        "#line "+std::to_string(shaderStartLine)+"\n"+
                                        currentSection;

            shaderSource = String::trim(shaderSource);

            if(currentShaderType == "vertex")
                shaderSources[ShaderType::Vertex] = shaderSource;
            else if(currentShaderType == "fragment")
                shaderSources[ShaderType::Fragment] = shaderSource;
            else if(currentShaderType == "compute")
                shaderSources[ShaderType::Compute] = shaderSource;
        }

        std::unordered_map<ShaderType, std::vector<uint32_t>> spirvShaders;

        for(const auto& [shaderType, shaderSource] : shaderSources)
        {
            spirvShaders[shaderType] = compileToSpirv(filepath, shaderType, shaderSource);
        }

        return createShaderFromSpirvImpl(spirvShaders);
    }
}
