#include "deviceOGL.h"
#include <glad/glad.h>

#include "commandListOGL.h"
#include "frameBufferOGL.h"
#include "graphicsPipelineOGL.h"
#include "indexBufferOGL.h"
#include "shaderOGL.h"
#include "uniformBufferOGL.h"
#include "vertexBufferOGL.h"
#include "windowOGL.h"

namespace Neon
{
    DeviceOGL::DeviceOGL(WindowOGL *window) : window(window)
    {

    }

    Ref<GraphicsPipeline> DeviceOGL::createGraphicsPipeline(GraphicsPipelineDescription graphicsPipelineDescription)
    {
        return makeRef<GraphicsPipelineOGL>(graphicsPipelineDescription);
    }

    Ref<CommandList> DeviceOGL::createCommandList()
    {
        return makeRef<CommandListOGL>();
    }

    Ref<IndexBuffer> DeviceOGL::createIndexBuffer(std::vector<uint32_t> data)
    {
        return makeRef<IndexBufferOGL>(data);
    }

    void DeviceOGL::submitCommandList(const Ref<CommandList> commandList)
    {
        dynamic_cast<CommandListOGL*>(commandList.get())->executeCommands();
    }

    void DeviceOGL::swapBuffers()
    {
        window->swapBuffers();
    }

    Ref<FrameBuffer> DeviceOGL::getSwapChainFrameBuffer()
    {
        return makeRef<FrameBufferOGL>(0);
    }

    Ref<Texture2D> DeviceOGL::createTexture2DImpl(uint32_t width, uint32_t height, TextureUsage usage,
                                                  TextureFormat format, uint8_t *data)
    {
        return nullptr;
        //return makeRef<Texture2DOGL>(width, height, usage, format, data);
    }

    Ref<VertexBuffer> DeviceOGL::createVertexBufferImpl(void *data, uint32_t elementCount, uint32_t elementSize)
    {
        return makeRef<VertexBufferOGL>(data, elementCount, elementSize);
    }

    Ref<Shader> DeviceOGL::createShaderFromSpirvImpl(
        std::unordered_map<ShaderType, std::vector<uint32_t>> shadersSpirv)
    {
        return makeRef<ShaderOGL>(shadersSpirv);
    }

    Ref<UniformBuffer> DeviceOGL::createUniformBufferImpl(void *data, uint32_t size)
    {
        return makeRef<UniformBufferOGL>(data, size);
    }
}
