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

    struct AABB
    {
        glm::vec3 min;
        glm::vec3 max;
    };

    class Mesh
    {
    public:
        Mesh() = default;

        void apply();
        void recalculateBounds();

        void setVertices(const std::vector<Vertex>& vertices);
        void setIndices(const std::vector<uint32_t>& indices);

        void setPrimitives(const std::vector<Primitive>& primitives);
        void addPrimitive(uint32_t startIndex, uint32_t indexCount);
        [[nodiscard]] const std::vector<Primitive>& getPrimitives() const;

        [[nodiscard]] const std::vector<Vertex>& getVertices() const;
        [[nodiscard]] const std::vector<uint32_t>& getIndices() const;

        AABB getBounds();

        [[nodiscard]] RHI::Buffer* getVertexBuffer();
        [[nodiscard]] RHI::Buffer* getIndexBuffer();

        void setReadable(bool readable);
    private:
        bool verticesDirty = true;
        bool indicesDirty = false;

        bool readable = false;

        std::vector<Vertex> vertices{};
        std::vector<uint32_t> indices{};
        std::vector<Primitive> primitives{};

        AABB bounds{};

        Box<RHI::Buffer> vertexBuffer = nullptr;
        Box<RHI::Buffer> indexBuffer = nullptr;
    };
}
