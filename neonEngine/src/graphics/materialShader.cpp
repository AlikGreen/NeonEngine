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

    MaterialShader::MaterialShader(const MaterialDescription& description)
    {
        name = description.name;
        device = Engine::getSystem<GraphicsSystem>()->getDevice();
        const RHI::ShaderReflection reflection = description.shader.get()->getShaderReflection();
        for(const auto& ub : reflection.uniformBlocks)
        {
            if(ub.name == "Properties")
                memberInfos = ub.members;
        }

        uint32_t requiredSize = 0;
        for (const auto& mem : memberInfos)
            requiredSize = std::max(requiredSize, mem.offset + mem.size);

        samplerInfos = reflection.samplers;

        if (cpuData.size() < requiredSize)
            cpuData.resize(requiredSize);

        RHI::InputLayout inputLayout{};
        inputLayout.addVertexBuffer<Vertex>(0);
        inputLayout.addVertexAttribute<glm::vec3>(0, 0); // Pos
        inputLayout.addVertexAttribute<glm::vec3>(0, 1); // Normal
        inputLayout.addVertexAttribute<glm::vec2>(0, 2); // UV

        RHI::DepthState depthState{};
        depthState.hasDepthTarget   = true;
        depthState.enableDepthTest  = description.depthTest;
        depthState.enableDepthWrite = description.depthWrite;

        RHI::RasterizerState rasterizerState{};
        rasterizerState.cullMode = RHI::CullMode::None; // Usually Back, but None is safe for debugging

        const RHI::RenderTargetsDescription targetsDesc{};

        RHI::BlendState blendState{};
        blendState.enableBlend = description.blendEnabled;
        blendState.srcColorFactor = description.srcColorBlendFactor;
        blendState.dstColorFactor = description.dstColorBlendFactor;
        blendState.srcAlphaFactor = description.srcAlphaBlendFactor;
        blendState.dstAlphaFactor = description.dstAlphaBlendFactor;

        RHI::GraphicsPipelineDescription pipelineDescription{};
        pipelineDescription.shader             = description.shader.get();
        pipelineDescription.inputLayout        = inputLayout;
        pipelineDescription.targetsDescription = targetsDesc;
        pipelineDescription.depthState         = depthState;
        pipelineDescription.rasterizerState    = rasterizerState;
        pipelineDescription.blendState         = blendState;

        pipeline = device->createPipeline(pipelineDescription);

        propertiesBuffer = device->createUniformBuffer();

        defaultTexture = Engine::getSystem<GraphicsSystem>()->getDefaultTexture();
        RHI::SamplerDescription samplerDescription{};
        defaultSampler = device->createSampler(samplerDescription);
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
        if(dirty && !cpuData.empty())
        {
            commandList->reserveBuffer(propertiesBuffer, cpuData.size());
            commandList->updateBuffer(propertiesBuffer, cpuData);
            dirty = false;
        }

        if(propertiesBuffer != nullptr && !cpuData.empty())
            commandList->setUniformBuffer("Properties", propertiesBuffer);

        for(const auto& samplerInfo : samplerInfos)
        {
            if(!textures.contains(samplerInfo.name))
                commandList->setTexture(samplerInfo.name, defaultTexture);

            if(!samplers.contains(samplerInfo.name))
                commandList->setSampler(samplerInfo.name, defaultSampler);
        }

        for(const auto& [name, texture] : textures)
        {
            commandList->setTexture(name, texture);
        }

        for(const auto& [name, sampler] : samplers)
        {
            commandList->setSampler(name, sampler);
        }
    }

    MaterialShader MaterialShader::createPBR()
    {
        AssetManager& assetManager = Engine::getAssetManager();
        const auto shaderHandle = assetManager.loadAsset<Rc<RHI::Shader>>("shaders/pbr.glsl");

        MaterialDescription desc{};
        desc.name = "PBR";
        desc.shader = shaderHandle;
        desc.cullMode = RHI::CullMode::Back;
        desc.blendEnabled = false;
        desc.depthTest = true;
        desc.depthWrite = true;

        return MaterialShader(desc);
    }

    MaterialShader MaterialShader::createEquirectangularSkybox()
    {
        AssetManager& assetManager = Engine::getAssetManager();
        const auto shaderHandle = assetManager.loadAsset<Rc<RHI::Shader>>("shaders/skybox.glsl");

        MaterialDescription desc{};
        desc.name = "Skybox equirectangular";
        desc.shader = shaderHandle;
        desc.cullMode = RHI::CullMode::Front;
        desc.blendEnabled = false;
        desc.depthTest = false;
        desc.depthWrite = false;

        return MaterialShader(desc);
    }
}
