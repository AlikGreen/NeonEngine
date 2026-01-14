#include "shaderImporter.h"

#include "shaderCompiler.h"
#include "core/engine.h"
#include "graphics/renderSystem.h"
#include "util/file.h"

namespace Neon
{
    void* ShaderImporter::load(const std::string &filepath)
    {
        const auto& device = Engine::getSystem<GraphicsSystem>()->getDevice();

        const std::string dir = std::filesystem::path(filepath).parent_path().string();

        RHI::ShaderCompileDescription compileDesc{};
        compileDesc.path = filepath;
        compileDesc.source = File::readFileText(filepath.c_str());
        compileDesc.includePaths.push_back(dir);

        auto spirv = RHI::ShaderCompiler::compile(compileDesc);
        auto shader = device->createShader(spirv);
        shader->compile();
        return new Rc(std::move(shader));
    }
}
