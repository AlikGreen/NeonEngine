#include "imageSerializer.h"
#include "stb_image.h"

namespace Neon
{
    void * ImageSerializer::load(const std::string &filePath)
    {
        int w, h, channels;
        const unsigned char *pixels = stbi_load(filePath.c_str(), &w, &h, &channels, 4);
        if (!pixels)
        {
            fprintf(stderr, "stb_image load failed: %s\n", stbi_failure_reason());
            return NULL;
        }
    }

    void ImageSerializer::serialize(const std::string &filePath)
    {
    }

    void * ImageSerializer::deserialize(const std::string &filePath)
    {
    }
}
