#include "deviceOGL.h"
#include <glad/glad.h>

#include "bufferOGL.h"
#include "commandListOGL.h"
#include "frameBufferOGL.h"
#include "graphicsPipelineOGL.h"
#include "samplerOGL.h"
#include "shaderOGL.h"
#include "textureOGL.h"
#include "windowOGL.h"

namespace NRHI
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

    Ref<Texture> DeviceOGL::createTexture(TextureDescription textureDescription)
    {
        return makeRef<TextureOGL>(textureDescription);
    }

    Ref<Sampler> DeviceOGL::createSampler(SamplerDescription samplerDescription)
    {
        return makeRef<SamplerOGL>(samplerDescription);
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


    Ref<Shader> DeviceOGL::createShaderFromSpirvImpl(
        std::unordered_map<ShaderType, std::vector<uint32_t>> shadersSpirv)
    {
        return makeRef<ShaderOGL>(shadersSpirv);
    }
}
