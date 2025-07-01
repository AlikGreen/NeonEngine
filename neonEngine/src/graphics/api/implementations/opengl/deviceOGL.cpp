#include "deviceOGL.h"
#include <glad/glad.h>

#include "bufferOGL.h"
#include "commandListOGL.h"
#include "frameBufferOGL.h"
#include "graphicsPipelineOGL.h"
#include "shaderOGL.h"
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

    Ref<Buffer> DeviceOGL::createIndexBuffer()
    {
        return makeRef<BufferOGL>(GL_ELEMENT_ARRAY_BUFFER);
    }

    Ref<Buffer> DeviceOGL::createUniformBuffer()
    {
        return makeRef<BufferOGL>(GL_UNIFORM_BUFFER);
    }

    Ref<Buffer> DeviceOGL::createVertexBuffer()
    {
        return makeRef<BufferOGL>(GL_ARRAY_BUFFER);
    }

    void DeviceOGL::submit(const Ref<CommandList> commandList)
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

    Ref<Shader> DeviceOGL::createShaderFromSpirvImpl(
        std::unordered_map<ShaderType, std::vector<uint32_t>> shadersSpirv)
    {
        return makeRef<ShaderOGL>(shadersSpirv);
    }
}
