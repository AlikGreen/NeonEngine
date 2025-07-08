#pragma once
#include <tiny_gltf.h>

#include "graphics/mesh.h"
#include "prefab.h"
#include "asset/assetHandle.h"
#include "asset/assetSerializer.h"
#include "graphics/components/material.h"

namespace Neon
{
class PrefabSerializerGLB final : public AssetSerializer
{
public:
    Prefab* load(std::string filePath) override;
    void serialize(std::string filePath) override;
    Prefab* deserialize(std::string filePath) override;
private:
    static AssetHandle processMaterial(const tinygltf::Material& material, const tinygltf::Model& model);
    static Mesh* createMesh(const tinygltf::Mesh &mesh, const tinygltf::Model &model);
    static AssetHandle loadTexture(const tinygltf::Texture& texture, const tinygltf::Model& model, bool isSrgb);
};
}
