#pragma once
#include "shader.h"
#include "asset/assetLoader.h"

namespace Neon
{
class ShaderLoader final : public AssetLoader
{
public:
    void* load(const std::string &filepath) override;
};
}