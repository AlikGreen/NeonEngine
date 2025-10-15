#pragma once
#include <tiny_gltf.h>

#include "graphics/mesh.h"
#include "core/prefab.h"
#include "asset/assetHandle.h"
#include "asset/assetLoader.h"
#include "graphics/components/material.h"

namespace Neon
{
class PrefabLoaderGLB final : public AssetLoader
{
public:
    void* load(const std::string& filePath) override;

private:

    static bool loadModel(tinygltf::Model& model, const std::string& filePath);
    static std::vector<AssetHandle> processMaterials(const tinygltf::Model& model);
    static void processNodes(const tinygltf::Model& model, Prefab& prefab, const std::vector<AssetHandle>& materials, const AssetRef<Material>& defaultMaterial);

    static void setupTransform(Entity& entity, const tinygltf::Node& node);
    static void setupMeshRenderer(Entity& entity, AssetHandle meshHandle, const tinygltf::Mesh& mesh, const AssetRef<Material>& defaultMaterial, const std::vector<AssetHandle>& materials);
    static void setupPBRProperties(Material* mat, const tinygltf::Material& material, const tinygltf::Model& model);
    static void setupTextureProperties(Material* mat, const tinygltf::Material& material, const tinygltf::Model& model);
    static void setupMaterialFlags(Material* mat, const tinygltf::Material& material);

    static AssetHandle processMaterial(const tinygltf::Material& material, const tinygltf::Model& model);
    static Mesh* createMesh(const tinygltf::Mesh &mesh, const tinygltf::Model &model);

    static std::vector<glm::vec3> extractVertexPositions(const tinygltf::Primitive& primitive, const tinygltf::Model& model);
    static std::vector<glm::vec3> extractVertexNormals(const tinygltf::Primitive& primitive, const tinygltf::Model& model);
    static std::vector<glm::vec2> extractVertexUVs(const tinygltf::Primitive& primitive, const tinygltf::Model& model);
    static std::vector<uint32_t> extractIndices(const tinygltf::Primitive& primitive, const tinygltf::Model& model);

    static AssetHandle loadTexture(const tinygltf::Texture& texture, const tinygltf::Model& model, bool isSrgb);

    static RHI::PixelFormat tinyGltfGetPixelFormat(const tinygltf::Image &img);
    static RHI::PixelType tinyGltfGetPixelType(const tinygltf::Image &img);
};
}
