#pragma once
#include <glad/glad.h>

#include "graphics/api/enums/mipmapFilter.h"
#include "graphics/api/enums/shaderType.h"
#include "graphics/api/enums/textureFilter.h"
#include "graphics/api/enums/textureFormat.h"
#include "graphics/api/enums/textureWrap.h"
#include "input/keyCodes.h"

namespace Neon
{
class ConvertOGL
{
public:
    static GLenum typeinfoToGL(const std::type_info* type);
    static GLenum shaderTypeToGL(ShaderType type);
    static GLenum textureFormatToGL(TextureFormat format);
    static GLenum textureFormatToGLType(TextureFormat format);
    static uint32_t getComponentCount(const std::type_info* type);
    static KeyCode keyCodeFromGLFW(int keyCode);
    static KeyMod keyModFromGLFW(int mod);
    static MouseButton mouseButtonFromGLFW(int button);
    static GLenum textureWrapToGL(TextureWrap wrap);
    static GLenum textureFilterCombineToGL(TextureFilter filter, MipmapFilter mipmapFilter);
};
}
