#include "shader.h"

#include <fstream>
#include <iostream>
#include <unordered_map>

#include <spirv_cross.hpp>
#include <spirv_glsl.hpp>

#include "../../neonEngine.h"
#include "../../util/file.h"
#include "../renderSystem.h"

namespace Neon
{
    Shader::Shader(std::string filePath)
    {
        std::string fullSource = File::readFileText(filePath.c_str());

        std::unordered_map<std::string, std::string> result;
        const std::string tag = "#type";
        size_t pos = fullSource.find(tag);
        while (pos != std::string::npos)
        {
            // find end of line after "#type XYZ"
            const size_t eol = fullSource.find_first_of("\r\n", pos);
            // extract "XYZ"
            std::string type = fullSource.substr(pos + tag.size() + 1, eol - (pos + tag.size() + 1));
            // find start of next section
            const size_t next = fullSource.find(tag, eol);
            // grab everything from end-of-line (skip the newline) up to next tag (or EOF)
            const size_t startOfContent = fullSource.find_first_not_of("\r\n", eol);
            const std::string src = (next == std::string::npos)
                ? fullSource.substr(startOfContent)
                : fullSource.substr(startOfContent, next - startOfContent);
            result[type] = src;
            pos = next;
        }

        for (const auto&[type, src]: result)
        {
            std::cout << src << std::endl;

            if(type == "fragment" || type == "pixel")
                shadersData.push_back(ShaderData{filePath, src, shaderc_fragment_shader, SDL_GPU_SHADERFORMAT_SPIRV });
            else if(type == "vertex")
                shadersData.push_back(ShaderData{filePath, src, shaderc_vertex_shader, SDL_GPU_SHADERFORMAT_SPIRV  });
        }
    }

    SDL_GPUShader* Shader::compileShader(const ShaderData &shaderData)
    {
        shaderc::Compiler compiler;
        shaderc::CompileOptions options;
        options.SetOptimizationLevel(shaderc_optimization_level_performance);
        options.SetTargetEnvironment(shaderc_target_env_vulkan, shaderc_env_version_vulkan_1_1); // Explicit Vulkan 1.3
        options.SetTargetSpirv(shaderc_spirv_version_1_3);

        shaderc::SpvCompilationResult module = compiler.CompileGlslToSpv(shaderData.source, shaderData.shaderStage, shaderData.filePath.c_str(), options);

        if (module.GetCompilationStatus() != shaderc_compilation_status_success)
        {
            std::cerr << "GLSL→SPIR‑V error: " << module.GetErrorMessage() << "\n";
        }

        std::vector<Uint8> spirv(module.cbegin(), module.cend());
        std::vector<uint32_t> spirvWords(module.cbegin(), module.cend());
        std::ofstream out("shader.spv", std::ios::binary);
        out.write(reinterpret_cast<const char*>(spirvWords.data()), spirvWords.size() * sizeof(uint32_t));
        out.close();

        SDL_GPUShaderStage sdlStage;

        switch (shaderData.shaderStage)
        {
            case shaderc_glsl_vertex_shader:
                sdlStage = SDL_GPU_SHADERSTAGE_VERTEX;
                break;
            case shaderc_glsl_fragment_shader:
                sdlStage = SDL_GPU_SHADERSTAGE_FRAGMENT;
                break;
            default:
                return nullptr;
        }

        DescriptorCounts descriptorCounts = reflectDescriptorCounts(spirvWords); // Error in this function

        SDL_GPUShaderCreateInfo shaderInfo;
        shaderInfo.code = reinterpret_cast<const Uint8 *>(spirvWords.data());
        shaderInfo.code_size = spirvWords.size() * sizeof(uint32_t);
        shaderInfo.entrypoint = "main";
        shaderInfo.format = shaderData.shaderFormat;
        shaderInfo.stage = sdlStage;
        shaderInfo.num_samplers = descriptorCounts.samplers;
        shaderInfo.num_uniform_buffers = descriptorCounts.uniformBuffers;
        shaderInfo.num_storage_buffers = descriptorCounts.storageBuffers;
        shaderInfo.num_storage_textures = descriptorCounts.storageTextures;

        RenderSystem* renderSystem = Engine::getInstance()->getSystem<RenderSystem>();
        SDL_GPUShader* shader = SDL_CreateGPUShader(renderSystem->getDevice(), &shaderInfo);

        if (shader == nullptr)
        {
            SDL_Log("Failed to create shader!");
            spirv.clear();
            return nullptr;
        }

        spirv.clear();
        return shader;
    }

    Shader::DescriptorCounts Shader::reflectDescriptorCounts(const std::vector<uint32_t> &spirvWords)
    {
        // Create a GLSL compiler just to reflect
        spirv_cross::CompilerGLSL compiler(spirvWords.data(), spirvWords.size());

        // Query all descriptor resources
        auto resources = compiler.get_shader_resources();

        DescriptorCounts counts;
        // Combined-image+samplers
        counts.samplers = static_cast<uint32_t>(resources.sampled_images.size());
        // In Vulkan HLSL land you can also have separate-samplers:
        counts.samplers += static_cast<uint32_t>(resources.separate_samplers.size());

        // Uniform buffers (UBOs / ConstantBuffers)
        counts.uniformBuffers =
            static_cast<uint32_t>(resources.uniform_buffers.size());

        // Storage buffers (SSBOs / StructuredBuffers / UAV buffers)
        counts.storageBuffers =
            static_cast<uint32_t>(resources.storage_buffers.size());

        // Storage textures (image load/store), including buffer‐backed ones
        counts.storageTextures =
            static_cast<uint32_t>(resources.storage_images.size())
          + static_cast<uint32_t>(resources.separate_images.size());

        return counts;
    }

    void Shader::compile()
    {
        for (const auto& shaderData: shadersData)
        {
            if(shaderData.shaderStage == shaderc_glsl_vertex_shader)
                vertexShader = compileShader(shaderData);
            if(shaderData.shaderStage == shaderc_glsl_fragment_shader)
                fragmentShader = compileShader(shaderData);
        }
    }
}
