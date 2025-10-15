#include "shaderLoader.h"

#include "core/engine.h"
#include "graphics/renderSystem.h"
#include "util/file.h"

namespace Neon
{
    void * ShaderLoader::load(const std::string &filepath)
    {
        auto* device = Engine::getSystem<RenderSystem>()->getDevice();
        return device->createShaderFromSource(File::readFileText(filepath.c_str()), filepath);;
    }
}
