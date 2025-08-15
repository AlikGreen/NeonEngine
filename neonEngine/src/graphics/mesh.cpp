#include "mesh.h"

#include <tiny_gltf.h>

#include "renderSystem.h"
#include "core/engine.h"

namespace Neon
{
    void Mesh::apply()
    {
        const auto device = Engine::getSystem<RenderSystem>()->getDevice();

        vertexBuffer = Scope<NRHI::Buffer>(device->createVertexBuffer());
        indexBuffer  = Scope<NRHI::Buffer>(device->createIndexBuffer());

        const Scope<NRHI::CommandList> cl =  Scope<NRHI::CommandList>(device->createCommandList());
        cl->begin();

        cl->reserveBuffer(vertexBuffer.get(), vertices.size() * sizeof(Vertex));
        cl->updateBuffer(vertexBuffer.get(), vertices);

        cl->reserveBuffer(indexBuffer.get(), indices.size() * sizeof(uint32_t));
        cl->updateBuffer(indexBuffer.get(), indices);

        device->submit(cl.get());
    }
}
