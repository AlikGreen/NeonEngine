#pragma once
#include <vector>

#include <neonRHI/neonRHI.h>
#include "glm/glm.hpp"

namespace Neon
{
    struct Vertex
    {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 uv;
    };

    struct Primitive
    {
        uint32_t indexStart;
        uint32_t indexCount;
    };

    class Mesh
    {
    public:
        Mesh() = default;

        void apply();

        std::vector<Vertex> vertices{};
        std::vector<uint32_t> indices{};
        std::vector<Primitive> primitives{};

        Scope<NRHI::Buffer> vertexBuffer = nullptr;
        Scope<NRHI::Buffer> indexBuffer = nullptr;
    };
}
