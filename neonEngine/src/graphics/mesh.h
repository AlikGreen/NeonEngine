#pragma once
#include <vector>

#include "api/buffer.h"
#include "asset/asset.h"
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

    class Mesh final : public Asset
    {
    public:
        Mesh() = default;

        void apply();

        std::vector<Vertex> vertices{};
        std::vector<uint32_t> indices{};
        std::vector<Primitive> primitives{};

        Ref<Buffer> vertexBuffer = nullptr;
        Ref<Buffer> indexBuffer = nullptr;
    };
}
