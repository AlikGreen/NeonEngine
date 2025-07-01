#pragma once
#include <tiny_gltf.h>

#include "graphics/mesh.h"
#include "prefab.h"
#include "asset/assetSerializer.h"

namespace Neon
{
class PrefabSerializerGLB final : public AssetSerializer
{
public:
    Prefab* load(std::string filePath) override;
    void serialize(std::string filePath) override;
    Prefab* deserialize(std::string filePath) override;
private:
    static Mesh* createMesh(const tinygltf::Mesh &mesh, const tinygltf::Model &model);
};
}
