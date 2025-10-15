#pragma once
#include "image.h"
#include "shader.h"

namespace Neon
{

using MaterialPropertyValue = std::variant<
    float,
    int,
    bool,
    glm::vec2,
    glm::vec3,
    glm::vec4,
    AssetRef<Image>
>;

struct MaterialPropertyDesc
{
    std::string name;
    MaterialPropertyValue value;
};

class MaterialShader
{
public:
    explicit MaterialShader(RHI::Shader* shader);

    void setProperty(const std::string& name, float value);
    void setProperty(const std::string& name, int   value);
    void setProperty(const std::string& name, bool  value);

    void setProperty(const std::string& name, glm::vec2 value);
    void setProperty(const std::string& name, glm::vec3 value);
    void setProperty(const std::string& name, glm::vec4 value);

    void setProperty(const std::string& name, Image* value);

    [[nodiscard]] std::vector<MaterialPropertyDesc>& getProperties() const;
private:
    std::vector<MaterialPropertyDesc> properties{};
    RHI::Shader* shader = nullptr;
};
}
