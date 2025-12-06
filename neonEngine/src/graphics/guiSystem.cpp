#include "guiSystem.h"

#include "renderSystem.h"
#include "core/engine.h"

namespace Neon
{

    void GuiSystem::preStartup()
    {
        const std::vector positions {
            glm::vec2(-1, -1),
            glm::vec2(-1,  1),
            glm::vec2( 1,  1),
            glm::vec2( 1, -1)
        };

        const std::vector<uint32_t> indices = {
            0, 1, 2,
            0, 2, 3
        };

        const auto device = Engine::getSystem<RenderSystem>()->getDevice();

        quadVertexBuffer = Box<RHI::Buffer>(device->createVertexBuffer());
        quadIndexBuffer  = Box<RHI::Buffer>(device->createIndexBuffer());

        const auto cl =  Box<RHI::CommandList>(device->createCommandList());
        cl->begin();

        cl->reserveBuffer(quadVertexBuffer.get(), positions.size() * sizeof(glm::vec2));
        cl->updateBuffer(quadVertexBuffer.get(), positions);

        cl->reserveBuffer(quadIndexBuffer.get(), indices.size() * sizeof(uint32_t));
        cl->updateBuffer(quadIndexBuffer.get(), indices);

        device->submit(cl.get());
    }

    void GuiSystem::preUpdate()
    {

    }
}
