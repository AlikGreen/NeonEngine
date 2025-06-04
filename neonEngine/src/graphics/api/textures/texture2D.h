#pragma once
#include "texture.h"

namespace Neon
{
class Texture2D : public Texture
{
public:
    ~Texture2D() override = default;

    void load(const std::string& filePath) override {};

    void serialize(AssetStream& stream) override {};
    void deserialize(AssetStream& stream) override {};
};
}
