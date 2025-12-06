#include "mesh.h"

#include <tiny_gltf.h>

#include "renderSystem.h"
#include "core/engine.h"

namespace Neon
{
    void Mesh::apply()
    {
        if(primitives.empty()) primitives.emplace_back(0, indices.size());

        const auto device = Engine::getSystem<RenderSystem>()->getDevice();

        vertexBuffer = Box<RHI::Buffer>(device->createVertexBuffer());
        indexBuffer  = Box<RHI::Buffer>(device->createIndexBuffer());

        const auto cl =  Box<RHI::CommandList>(device->createCommandList());
        cl->begin();

        cl->reserveBuffer(vertexBuffer.get(), vertices.size() * sizeof(Vertex));
        cl->updateBuffer(vertexBuffer.get(), vertices);

        cl->reserveBuffer(indexBuffer.get(), indices.size() * sizeof(uint32_t));
        cl->updateBuffer(indexBuffer.get(), indices);

        device->submit(cl.get());

        recalculateBounds();

        this->vertices.clear();
        this->indices.clear();

        verticesDirty = false;
        indicesDirty = false;
    }

    void Mesh::recalculateBounds()
    {
        bounds.min = glm::vec3(std::numeric_limits<float>::min());
        bounds.max = glm::vec3(std::numeric_limits<float>::max());

        for(Vertex vert : vertices)
        {
            bounds.min = glm::min(bounds.min, vert.position);
            bounds.max = glm::max(bounds.max, vert.position);
        }
    }

    void Mesh::setVertices(const std::vector<Vertex> &vertices)
    {
        this->vertices = vertices;
        verticesDirty = true;
    }

    void Mesh::setIndices(const std::vector<uint32_t> &indices)
    {
        this->indices = indices;
        indicesDirty = true;
    }

    void Mesh::setPrimitives(const std::vector<Primitive> &primitives)
    {
        this->primitives = primitives;
    }

    void Mesh::addPrimitive(uint32_t startIndex, uint32_t indexCount)
    {
        primitives.emplace_back(startIndex, indexCount);
    }

    const std::vector<Primitive> & Mesh::getPrimitives() const
    {
        return primitives;
    }

    const std::vector<Vertex>& Mesh::getVertices() const
    {
        Debug::ensure(readable, "Mesh is not readable on the CPU.");
        return vertices;
    }

    const std::vector<uint32_t>& Mesh::getIndices() const
    {
        Debug::ensure(readable, "Mesh is not readable on the CPU.");
        return indices;
    }

    AABB Mesh::getBounds()
    {
        if(verticesDirty) recalculateBounds();
        return bounds;
    }

    RHI::Buffer * Mesh::getVertexBuffer()
    {
        if(verticesDirty)
        {
            apply();
        }
        return vertexBuffer.get();
    }

    RHI::Buffer * Mesh::getIndexBuffer()
    {
        if(indicesDirty)
        {
            apply();
        }
        return indexBuffer.get();
    }

    void Mesh::setReadable(const bool readable)
    {
        this->readable = readable;
    }
}
