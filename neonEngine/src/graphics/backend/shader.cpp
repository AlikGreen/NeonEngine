#include "shader.h"

#include <fstream>
#include <iostream>
#include <unordered_map>

#include <spirv_cross.hpp>
#include <spirv_glsl.hpp>

#include "spirv_hlsl.hpp"
#include "spirv_msl.hpp"
#include "../../neonEngine.h"
#include "../../util/file.h"
#include "../renderSystem.h"

namespace Neon
{
    Shader::Shader(const std::string &filePath)
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
            if(type == "fragment" || type == "pixel")
                shadersData.push_back(ShaderData{filePath, src, shaderc_fragment_shader, SDL_GPU_SHADERFORMAT_SPIRV });
            else if(type == "vertex")
                shadersData.push_back(ShaderData{filePath, src, shaderc_vertex_shader, SDL_GPU_SHADERFORMAT_SPIRV  });
        }
    }

    std::vector<uint32_t> Shader::compileShaderToSpirv(const std::string &source, const shaderc_shader_kind kind, const std::string &debugFileName)
    {
        const shaderc::Compiler glslCompiler;
        shaderc::CompileOptions options;

        // Essential options for Vulkan
        options.SetTargetEnvironment(shaderc_target_env_vulkan, shaderc_env_version_vulkan_1_1);
        options.SetTargetSpirv(shaderc_spirv_version_1_3);
        options.SetOptimizationLevel(shaderc_optimization_level_performance);

        const shaderc::SpvCompilationResult spvResult = glslCompiler.CompileGlslToSpv(
            source, kind, debugFileName.c_str(), options
        );

        if (spvResult.GetCompilationStatus() != shaderc_compilation_status_success) {
            throw std::runtime_error("GLSL→SPIR-V failed: " + spvResult.GetErrorMessage());
        }

        std::vector spirv(spvResult.cbegin(), spvResult.cend());
        return spirv;
    }

    std::vector<uint8_t> Shader::compileShaderForBackend(std::vector<uint32_t> spirv, BackendAPI backend)
    {
        switch (backend)
        {
            case BackendAPI::Vulkan:
            {
                const uint8_t* bytePtr = reinterpret_cast<const uint8_t*>(spirv.data());
                return {bytePtr, bytePtr + spirv.size() * sizeof(uint32_t)};
            }

            case BackendAPI::Directx11:
            case BackendAPI::Directx12:
            {
                spirv_cross::CompilerHLSL hlslCompiler(spirv);
                spirv_cross::CompilerHLSL::Options hlslOptions;

                // Configure HLSL version
                hlslOptions.shader_model = (backend == BackendAPI::Directx12) ? 60 : 50;
                hlslCompiler.set_hlsl_options(hlslOptions);

                // Remap resources for HLSL
                spirv_cross::ShaderResources resources = hlslCompiler.get_shader_resources();
                for (auto& resource : resources.sampled_images) {
                    hlslCompiler.set_decoration(resource.id, spv::DecorationBinding, 0);
                }

                std::string hlsl = hlslCompiler.compile();
                return {hlsl.begin(), hlsl.end()};
            }

            case BackendAPI::Metal:
            {
                spirv_cross::CompilerMSL mslCompiler(spirv);
                spirv_cross::CompilerMSL::Options mslOptions;

                // Configure Metal version
                mslOptions.msl_version = spirv_cross::CompilerMSL::Options::make_msl_version(2, 3);
                mslCompiler.set_msl_options(mslOptions);

                // Set up resource bindings
                spirv_cross::ShaderResources resources = mslCompiler.get_shader_resources();
                for (auto& resource : resources.sampled_images)
                    {
                    uint32_t binding = mslCompiler.get_decoration(resource.id, spv::DecorationBinding);
                    mslCompiler.set_decoration(resource.id, spv::DecorationBinding, binding);
                }

                std::string msl = mslCompiler.compile();
                return {msl.begin(), msl.end()};
            }

            default:
                throw std::runtime_error("Unsupported backend API");
        }
    }

    SDL_GPUShader* Shader::compileSDLShader(const ShaderData &shaderData)
    {
        auto* renderSystem = Engine::getInstance()->getSystem<RenderSystem>();

        std::vector<uint32_t> spirv = compileShaderToSpirv(shaderData.source, shaderData.shaderStage, shaderData.filePath);
        std::vector<uint8_t> shaderCode = compileShaderForBackend(spirv, renderSystem->getDevice()->getBackendApi());

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

        const DescriptorCounts descriptorCounts = reflectDescriptorCounts(spirv); // Error in this function

        SDL_GPUShaderCreateInfo shaderInfo;
        shaderInfo.code = shaderCode.data();
        shaderInfo.code_size = shaderCode.size();
        shaderInfo.entrypoint = "main";
        shaderInfo.format = shaderData.shaderFormat;
        shaderInfo.stage = sdlStage;
        shaderInfo.num_samplers = descriptorCounts.samplers;
        shaderInfo.num_uniform_buffers = descriptorCounts.uniformBuffers;
        shaderInfo.num_storage_buffers = descriptorCounts.storageBuffers;
        shaderInfo.num_storage_textures = descriptorCounts.storageTextures;

        SDL_GPUShader* shader = SDL_CreateGPUShader(*renderSystem->getDevice(), &shaderInfo);
        spirv.clear();

        if (shader == nullptr)
        {
            throw std::runtime_error("Failed to create shader shader");
            return nullptr;
        }

        return shader;
    }

    Shader::DescriptorCounts Shader::reflectDescriptorCounts(const std::vector<uint32_t> &spirv)
    {
        // Create a GLSL compiler just to reflect
        spirv_cross::CompilerGLSL compiler(spirv.data(), spirv.size());

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

    SDL_GPUShader * Shader::getVertexShader() const
    {
        return vertexShader;
    }

    SDL_GPUShader * Shader::getFragmentShader() const
    {
        return fragmentShader;
    }

    void Shader::compile()
    {
        for (const auto& shaderData: shadersData)
        {
            if(shaderData.shaderStage == shaderc_glsl_vertex_shader)
                vertexShader = compileSDLShader(shaderData);
            if(shaderData.shaderStage == shaderc_glsl_fragment_shader)
                fragmentShader = compileSDLShader(shaderData);
        }
    }

    void Shader::dispose() const
    {
        const auto* renderSystem = Engine::getInstance()->getSystem<RenderSystem>();

        if(fragmentShader != nullptr)
            SDL_ReleaseGPUShader(*renderSystem->getDevice(), fragmentShader);

        if(vertexShader != nullptr)
            SDL_ReleaseGPUShader(*renderSystem->getDevice(), vertexShader);
    }
}
