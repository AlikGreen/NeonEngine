#include "shaderLoader.h"

#include "core/engine.h"
#include "graphics/renderSystem.h"
#include "util/file.h"

namespace Neon
{
    void* ShaderLoader::load(const std::string &filepath)
    {
        const auto& device = Engine::getSystem<GraphicsSystem>()->getDevice();
        auto shader = device->createShaderFromSource(File::readFileText(filepath.c_str()), filepath);
        shader->compile();
        return new Rc(std::move(shader));
    }
}
