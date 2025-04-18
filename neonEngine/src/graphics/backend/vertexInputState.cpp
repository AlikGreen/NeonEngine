#include "vertexInputState.h"

namespace Neon
{
    std::vector<SDL_GPUVertexAttribute> VertexInputState::getVertexAttributes()
    {
        std::vector<SDL_GPUVertexAttribute> attributes;

        for (const auto attrib0: vertexAttributes)
        {
            int offset = 0;
            for (const auto attrib1: vertexAttributes)
            {
                if(attrib0.size == attrib1.slot && attrib0.location < attrib1.location)
                {
                    offset += attrib1.size;
                }
            }

            attributes.emplace_back(attrib0.location, attrib0.slot, attrib0.format, offset);
        }

        return attributes;
    }

    std::vector<SDL_GPUVertexBufferDescription> VertexInputState::getVertexBuffers()
    {
        return vertexBuffers;
    }
}
