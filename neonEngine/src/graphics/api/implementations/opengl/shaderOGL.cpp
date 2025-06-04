#include "shaderOGL.h"

#include <ranges>

#include "convertOGL.h"
#include "spirv_glsl.hpp"
#include "debug/assert.h"
#include "debug/logger.h"


namespace Neon
{
    ShaderOGL::ShaderOGL(const std::unordered_map<ShaderType, std::vector<uint32_t>> &shadersSpirv) : shadersSpirv(shadersSpirv) {  }

    std::string spirvToGlsl(const std::vector<uint32_t> &spirv)
    {
        spirv_cross::CompilerGLSL glsl_compiler(spirv);

        // 3. Set compilation options (VERY IMPORTANT for correct GLSL output)
        spirv_cross::CompilerGLSL::Options options;
        options.version = 460; // Target OpenGL GLSL 4.5
        options.es = false;   // Not OpenGL ES GLSL
        options.vulkan_semantics = false; // We want OpenGL semantics
        options.separate_shader_objects = true; // Often useful for modern GL

        // You can set many other options here, e.g.,
        // options.enable_420pack_extension = false;
        // options.flatten_multidimensional_arrays = true;
        // options.vertex.fixup_clipspace = true; // Adjust clip space for OpenGL
        // options.vertex.flip_vert_y = true;   // Flip Y for Vulkan -> OpenGL

        glsl_compiler.set_common_options(options);

        // 4. Perform the compilation to GLSL
        return glsl_compiler.compile();
    }

    void ShaderOGL::compile()
    {
        for (const auto& [type, shader]: shadersSpirv)
        {
            GLuint shaderHandle = glCreateShader(ConvertOGL::shaderTypeToGL(type));
            shaderHandles.push_back(shaderHandle);
            std::string shaderSource = spirvToGlsl(shader);
            const char* shaderSourceCStr = shaderSource.c_str();
            glShaderSource(shaderHandle, 1, &shaderSourceCStr, nullptr);
            glCompileShader(shaderHandle);

            int  success;
            char infoLog[512];
            glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &success);
            glGetShaderInfoLog(shaderHandle, 512, nullptr, infoLog);

            Assert::check<const char*>(success, "Shader compilation error: {}", infoLog);
        }

        handle = glCreateProgram();
        for (const GLuint shader: shaderHandles)
        {
            glAttachShader(handle, shader);
        }

        glLinkProgram(handle);

        for (const GLuint shader: shaderHandles)
        {
            glDeleteShader(shader);
        }
    }

    void ShaderOGL::dispose()
    {

    }

    void ShaderOGL::bind() const
    {
        glUseProgram(handle);
    }
}
