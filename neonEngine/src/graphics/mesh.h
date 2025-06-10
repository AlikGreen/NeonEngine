#pragma once
#include <vector>

#include "api/buffers/indexBuffer.h"
#include "api/buffers/vertexBuffer.h"
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

    class Mesh : public Asset
    {
    public:
        Mesh() = default;

        void apply();

        std::vector<Vertex> vertices{};
        std::vector<uint32_t> indices{};

        Ref<VertexBuffer> vertexBuffer = nullptr;
        Ref<IndexBuffer> indexBuffer = nullptr;
    };
}
