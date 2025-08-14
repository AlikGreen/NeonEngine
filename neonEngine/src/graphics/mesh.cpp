#include "mesh.h"

#include <tiny_gltf.h>

#include "renderSystem.h"
#include "core/engine.h"

namespace Neon
{
    void Mesh::apply()
    {
        const auto device = Engine::getSystem<RenderSystem>()->getDevice();

        vertexBuffer = device->createVertexBuffer();
        indexBuffer = device->createIndexBuffer();

        const Ref<NRHI::CommandList> cl =  device->createCommandList();
        cl->begin();

        cl->reserveBuffer(vertexBuffer, vertices.size() * sizeof(Vertex));
        cl->updateBuffer(vertexBuffer, vertices);

        cl->reserveBuffer(indexBuffer, indices.size() * sizeof(uint32_t));
        cl->updateBuffer(indexBuffer, indices);

        device->submit(cl);
    }
}
