#pragma once
#include "image.h"
#include "shader.h"
#include <variant>

#include "graphicsSystem.h"

namespace Neon
{


class MaterialShader
{

public:
    explicit MaterialShader(AssetRef<Rc<RHI::Shader>> shader);

    template<typename T>
    requires std::is_trivially_copyable_v<T>
    bool setProperty(const std::string& name, T const& value, const Rc<RHI::CommandList>& updateCmd = nullptr)
    {
        std::optional<RHI::ShaderUniformBlockMember> member = std::nullopt;
        for(const auto& mem : memberInfos)
        {
            if(mem.name == name)
                member = mem;
        }

        if(!member.has_value())
        {
            Log::error("MaterialShader::setProperty: Member not found: '{}'", name);
            return false;
        }

        if(member->size != sizeof(T))
        {
            Log::error("MaterialShader::setProperty: member size mismatch on member: '{}'", name);
            return false;
        }

        auto const* src = reinterpret_cast<uint8_t const*>(&value);
        uint8_t* dst = cpuData.data() + member->offset;

        if(memcmp(dst, src, member->size) == 0)
            return true; // no change

        memcpy(dst, src, member->size);
        dirty = true;
        return true;
    }

    template<typename T>
    requires std::is_trivially_copyable_v<T>
    std::optional<T> getProperty(const std::string& name) const
    {
        std::optional<RHI::ShaderUniformBlockMember> member = std::nullopt;
        for(const auto& mem : memberInfos)
        {
            if(mem.name == name)
                member = mem;
        }

        T out;
        memcpy(&out, cpuData.data() + member->offset, sizeof(T));
        return out;
    }

    bool setTexture(std::string name, Rc<RHI::TextureView> texture);
    bool setSampler(std::string name, Rc<RHI::Sampler> sampler);

    Rc<RHI::Pipeline> getPipeline();
    void bindUniforms(const Rc<RHI::CommandList>& commandList);

    static MaterialShader createPBR();
private:
    Rc<RHI::Device> device;
    Rc<RHI::Pipeline> pipeline;

    std::unordered_map<std::string, Rc<RHI::TextureView>> textures;
    std::unordered_map<std::string, Rc<RHI::Sampler>> samplers;
    std::vector<RHI::ShaderUniformBlockMember> memberInfos;
    std::vector<RHI::ShaderSampler> samplerInfos;

    bool dirty = true;
    std::vector<uint8_t> cpuData;
    Rc<RHI::Buffer> propertiesBuffer;
};
}
