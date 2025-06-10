#pragma once
#include "mesh.h"
#include "asset/assetSerializer.h"

namespace Neon
{
class MeshSerializerGLB final : public AssetSerializer
{
    Mesh* load(std::string filePath) override;
    void serialize(std::string filePath) override;
    Mesh* deserialize(std::string filePath) override;
};
}
