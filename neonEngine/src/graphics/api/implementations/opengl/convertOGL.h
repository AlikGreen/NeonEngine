#pragma once
#include <glad/glad.h>
#include <SDL3/SDL_keycode.h>

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
    static KeyCode keyCodeFromSDL(SDL_Keycode keyCode);
    static KeyMod keyModFromSDL(SDL_Keymod mod);
    static MouseButton mouseButtonFromSDL(uint8_t button);
};
}
