#include "shader.h"

#include <unordered_map>

#include "../../util/file.h"

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
            if(type == "fragment" || type == "pixel")
                createShader(src, SDL_GPU_SHADERSTAGE_FRAGMENT);
            else if(type == "vertex")
                createShader(src, SDL_GPU_SHADERSTAGE_VERTEX);
        }
    }

    void Shader::createShader(std::string source, SDL_GPUShaderStage stage)
    {
    }

    void Shader::compile()
    {
    }
}
