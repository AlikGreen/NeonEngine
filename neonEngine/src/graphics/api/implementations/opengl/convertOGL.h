#pragma once
#include <glad/glad.h>

#include "graphics/api/enums/shaderType.h"
#include "input/keyCodes.h"

namespace Neon
{
class ConvertOGL
{
public:
    static GLenum typeinfoToGL(const std::type_info* type);
    static GLenum shaderTypeToGL(ShaderType type);
    static uint32_t getComponentCount(const std::type_info* type);
    static KeyCode keyCodeFromGLFW(int keyCode);
    static KeyMod keyModFromGLFW(int mod);
    static MouseButton mouseButtonFromGLFW(int button);
};
}
