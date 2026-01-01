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

        [[nodiscard]] Rc<RHI::Buffer> getVertexBuffer();
        [[nodiscard]] Rc<RHI::Buffer> getIndexBuffer();
        [[nodiscard]] size_t getVertexCount() const;
        [[nodiscard]] size_t getIndexCount() const;

        void setReadable(bool readable);
    private:
        bool verticesDirty = true;
        bool indicesDirty = false;

        bool readable = false;

        std::vector<Vertex> vertices{};
        std::vector<uint32_t> indices{};
        std::vector<Primitive> primitives{};

        AABB bounds{};

        Rc<RHI::Buffer> vertexBuffer = nullptr;
        Rc<RHI::Buffer> indexBuffer = nullptr;

        size_t vertexCount = 0;
        size_t indexCount = 0;
    };
}
