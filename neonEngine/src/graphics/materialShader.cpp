#include "materialShader.h"

#include <utility>

namespace Neon
{
    struct Vertex
    {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 uv;
    };

    MaterialShader::MaterialShader(const AssetRef<Rc<RHI::Shader>> shader)
    {
        device = Engine::getSystem<GraphicsSystem>()->getDevice();
        const RHI::ShaderReflection reflection = shader.get()->getShaderReflection();
        for(const auto& ub : reflection.uniformBlocks)
        {
            if(ub.name == "Properties")
                memberInfos = ub.members;
        }

        uint32_t requiredSize = 0;
        for (const auto& mem : memberInfos)
            requiredSize = std::max(requiredSize, mem.offset + mem.size);

        if (cpuData.size() < requiredSize)
            cpuData.resize(requiredSize);

        RHI::InputLayout vertexInputState{};
        vertexInputState.addVertexBuffer<Vertex>(0);
        vertexInputState.addVertexAttribute<glm::vec3>(0, 0); // Pos
        vertexInputState.addVertexAttribute<glm::vec3>(0, 1); // Normal
        vertexInputState.addVertexAttribute<glm::vec2>(0, 2); // UV

        RHI::DepthState depthState{};
        depthState.hasDepthTarget   = true;
        depthState.enableDepthTest  = true;
        depthState.enableDepthWrite = true;

        RHI::RasterizerState rasterizerState{};
        rasterizerState.cullMode = RHI::CullMode::None; // Usually Back, but None is safe for debugging

        const RHI::RenderTargetsDescription targetsDesc{};

        RHI::BlendState blendState{};
        blendState.enableBlend = true;

        RHI::GraphicsPipelineDescription pipelineDescription{};
        pipelineDescription.shader             = shader.get();
        pipelineDescription.inputLayout        = vertexInputState;
        pipelineDescription.targetsDescription = targetsDesc;
        pipelineDescription.depthState         = depthState;
        pipelineDescription.rasterizerState    = rasterizerState;
        pipelineDescription.blendState         = blendState;

        pipeline = device->createPipeline(pipelineDescription);

        propertiesBuffer = device->createUniformBuffer();
    }

    bool MaterialShader::setTexture(std::string name, Rc<RHI::TextureView> texture)
    {
        bool containsSampler = false;

        for(const auto& samplerInfo : samplerInfos)
        {
            if(samplerInfo.name == name)
            {
                containsSampler = true;
                break;
            }
        }

        if(!containsSampler || texture.get() == nullptr)
            return false;

        if(textures.contains(name) && textures.at(name) == texture)
            return true;

        textures.emplace(name, texture);

        return true;
    }

    bool MaterialShader::setSampler(std::string name, Rc<RHI::Sampler> sampler)
    {
        bool containsSampler = false;

        for(const auto& samplerInfo : samplerInfos)
        {
            if(samplerInfo.name == name)
            {
                containsSampler = true;
                break;
            }
        }

        if(!containsSampler || sampler.get() == nullptr)
            return false;

        if(samplers.contains(name) && samplers.at(name) == sampler)
            return true;

        samplers.emplace(name, sampler);

        return true;
    }

    Rc<RHI::Pipeline> MaterialShader::getPipeline()
    {
        return pipeline;
    }

    void MaterialShader::bindUniforms(const Rc<RHI::CommandList>& commandList)
    {
        if(dirty)
        {
            commandList->reserveBuffer(propertiesBuffer, cpuData.size());
            commandList->updateBuffer(propertiesBuffer, cpuData);
            dirty = false;
        }

        commandList->setUniformBuffer("Properties", propertiesBuffer);

        for(const auto& [name, texture] : textures)
        {
            commandList->setTexture(name, texture);
        }
    }

    MaterialShader MaterialShader::createPBR()
    {
        AssetManager& assetManager = Engine::getAssetManager();
        const auto shaderHandle = assetManager.loadAsset<Rc<RHI::Shader>>("shaders/pbr.glsl");
        return MaterialShader(shaderHandle);
    }
}
