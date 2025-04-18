#pragma once
#include <vector>
#include <SDL3/SDL.h>
#include <glm/glm.hpp>

namespace Neon
{
class VertexInputState
{
public:
    template<typename  T>
    void addVertexBuffer(int slot)
    {
        vertexBuffers.emplace_back(slot, sizeof(T));
    }

    template<typename  T>
    void addVertexAttribute(const int vertexBufferSlot, const int location)
    {
        vertexAttributes.push_back({location, sizeof(T), vertexBufferSlot, getVertexElementFormat<T>()});
    }


    template <typename T>
    constexpr SDL_GPUVertexElementFormat getVertexElementFormat()
    {
        // Built-in scalar types
        if constexpr (std::is_same_v<T, float>)      return SDL_GPU_VERTEXELEMENTFORMAT_FLOAT;
        else if constexpr (std::is_same_v<T, int32_t>)   return SDL_GPU_VERTEXELEMENTFORMAT_INT;
        else if constexpr (std::is_same_v<T, uint32_t>)  return SDL_GPU_VERTEXELEMENTFORMAT_UINT;
        else if constexpr (std::is_same_v<T, int8_t>)    return SDL_GPU_VERTEXELEMENTFORMAT_BYTE4;
        else if constexpr (std::is_same_v<T, uint8_t>)   return SDL_GPU_VERTEXELEMENTFORMAT_UBYTE4;
        else if constexpr (std::is_same_v<T, int16_t>)   return SDL_GPU_VERTEXELEMENTFORMAT_SHORT4;
        else if constexpr (std::is_same_v<T, uint16_t>)  return SDL_GPU_VERTEXELEMENTFORMAT_USHORT4;

        // GLM vectors
        else if constexpr (std::is_same_v<T, glm::vec2>)  return SDL_GPU_VERTEXELEMENTFORMAT_FLOAT2;
        else if constexpr (std::is_same_v<T, glm::vec3>)  return SDL_GPU_VERTEXELEMENTFORMAT_FLOAT3;
        else if constexpr (std::is_same_v<T, glm::vec4>)  return SDL_GPU_VERTEXELEMENTFORMAT_FLOAT4;
        else if constexpr (std::is_same_v<T, glm::ivec2>) return SDL_GPU_VERTEXELEMENTFORMAT_INT2;
        else if constexpr (std::is_same_v<T, glm::ivec3>) return SDL_GPU_VERTEXELEMENTFORMAT_INT3;
        else if constexpr (std::is_same_v<T, glm::ivec4>) return SDL_GPU_VERTEXELEMENTFORMAT_INT4;
        else if constexpr (std::is_same_v<T, glm::uvec2>) return SDL_GPU_VERTEXELEMENTFORMAT_UINT2;
        else if constexpr (std::is_same_v<T, glm::uvec3>) return SDL_GPU_VERTEXELEMENTFORMAT_UINT3;
        else if constexpr (std::is_same_v<T, glm::uvec4>) return SDL_GPU_VERTEXELEMENTFORMAT_UINT4;

        // GLM matrices (treated as arrays of column vectors)
        else if constexpr (std::is_same_v<T, glm::mat2>)  return SDL_GPU_VERTEXELEMENTFORMAT_FLOAT2; // MAYBE WRONG
        else if constexpr (std::is_same_v<T, glm::mat3>)  return SDL_GPU_VERTEXELEMENTFORMAT_FLOAT3; // MAYBE WRONG
        else if constexpr (std::is_same_v<T, glm::mat4>)  return SDL_GPU_VERTEXELEMENTFORMAT_FLOAT4; // MAYBE WRONG

        // GLM quaternions (treated as vec4)
        else if constexpr (std::is_same_v<T, glm::quat>)  return SDL_GPU_VERTEXELEMENTFORMAT_FLOAT4;

        // Unsupported type (compile-time error)
        else static_assert(sizeof(T) == 0, "Unsupported vertex attribute type");
    }

private:
    friend class GraphicsPipeline;
    std::vector<SDL_GPUVertexAttribute> getVertexAttributes();
    std::vector<SDL_GPUVertexBufferDescription> getVertexBuffers();

    struct VertexAttribute
    {
        int location;
        int size;
        int slot;
        SDL_GPUVertexElementFormat format;
    };
    std::vector<VertexAttribute> vertexAttributes;

    std::vector<SDL_GPUVertexBufferDescription> vertexBuffers;
};
}
