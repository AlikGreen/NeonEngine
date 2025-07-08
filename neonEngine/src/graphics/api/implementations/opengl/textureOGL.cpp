#include "textureOGL.h"

#include <glad/glad.h>

#include "convertOGL.h"

namespace Neon
{
    TextureOGL::TextureOGL(const TextureDescription &description) : description(description)
    {
        width = description.width;
        height = description.height;
        depth = description.depth;

        glGenTextures(1, &handle);

        bind();

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, static_cast<int>(ConvertOGL::textureWrapToGL(description.wrapMode.x)));
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, static_cast<int>(ConvertOGL::textureWrapToGL(description.wrapMode.y)));
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, static_cast<int>(ConvertOGL::textureFilterCombineToGL(description.minFilter, description.mipmapFilter)));
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, static_cast<int>(ConvertOGL::textureFilterCombineToGL(description.magFilter, description.mipmapFilter)));

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, static_cast<int>(description.numMipmaps));
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    void TextureOGL::bind() const
    {
        glBindTexture(GL_TEXTURE_2D, handle);
    }

    void TextureOGL::unbind() const
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    uint32_t TextureOGL::getWidth()
    {
        return width;
    }

    uint32_t TextureOGL::getHeight()
    {
        return height;
    }

    uint32_t TextureOGL::getDepth()
    {
        return depth;
    }

    void TextureOGL::setData(const void *data) const
    {
        glTexImage2D(GL_TEXTURE_2D, 0, static_cast<int>(ConvertOGL::textureFormatToGL(description.format)), static_cast<int>(width), static_cast<int>(height), 0, ConvertOGL::textureFormatToGL(description.format), ConvertOGL::textureFormatToGLType(description.format), data);
    }
}
