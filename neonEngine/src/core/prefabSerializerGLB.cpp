#include "prefabSerializerGLB.h"

#include <tiny_gltf.h>

#include "graphics/components/meshRenderer.h"
#include "core/engine.h"
#include "debug/Logger.h"
#include "glm/gtc/type_ptr.hpp"
#include "graphics/renderSystem.h"
#include "graphics/api/texture.h"

namespace Neon
{
    Prefab* PrefabSerializerGLB::load(const std::string& filePath)
    {
        tinygltf::Model model;
        if (!loadModel(model, filePath))
        {
            return nullptr;
        }

        auto prefab = std::make_unique<Prefab>();
        Entity rootEntity = prefab->world.createEntity();
        rootEntity.addComponent<PrefabComponent>();

        auto materials = processMaterials(model);
        processNodes(model, *prefab, materials);

        return prefab.release();
    }

    void PrefabSerializerGLB::serialize(const std::string& filePath)
    {
    }

    Prefab* PrefabSerializerGLB::deserialize(const std::string& filePath)
    {
        return nullptr;
    }

    bool PrefabSerializerGLB::loadModel(tinygltf::Model& model, const std::string& filePath)
    {
        tinygltf::TinyGLTF loader;
        std::string err, warn;

        const bool success = loader.LoadBinaryFromFile(&model, &err, &warn, filePath);

        if (!warn.empty())
        {
            Logger::warning(warn);
        }
        if (!err.empty())
        {
            Logger::error("Failed to load model\nPath:{}\nError: {}", filePath, err);
        }

        return success;
    }

    std::vector<AssetHandle> PrefabSerializerGLB::processMaterials(const tinygltf::Model& model)
    {
        std::vector<AssetHandle> materials;
        materials.reserve(model.materials.size());

        for (const auto& material : model.materials)
        {
            materials.push_back(processMaterial(material, model));
        }

        return materials;
    }

    void PrefabSerializerGLB::processNodes(const tinygltf::Model& model, Prefab& prefab, const std::vector<AssetHandle>& materials)
    {
        const AssetRef<Material> defaultMaterial = Engine::getAssetManager().addAsset(new Material());

        for (const auto& node : model.nodes)
        {
            if (node.mesh < 0) continue;

            const tinygltf::Mesh& mesh = model.meshes[node.mesh];
            auto nMesh = createMesh(mesh, model);
            if (!nMesh) continue;

            const auto meshHandle = Engine::getAssetManager().addAsset(nMesh);
            Entity entity = prefab.world.createEntity();

            setupTransform(entity, node);
            setupMeshRenderer(entity, meshHandle, mesh, defaultMaterial, materials);
        }
    }

    void PrefabSerializerGLB::setupTransform(Entity& entity, const tinygltf::Node& node)
    {
        auto& transform = entity.getComponent<Transform>();

        if (node.translation.size() == 3)
        {
            transform.setPosition(glm::vec3(node.translation[0], node.translation[1], node.translation[2]));
        }
        if (node.rotation.size() == 4)
        {
            transform.setRotation(eulerAngles(glm::quat(
                static_cast<float>(node.rotation[3]),
                static_cast<float>(node.rotation[0]),
                static_cast<float>(node.rotation[1]),
                static_cast<float>(node.rotation[2]))));
        }
        if (node.scale.size() == 3)
        {
            transform.setScale(glm::vec3(node.scale[0], node.scale[1], node.scale[2]));
        }
    }

    void PrefabSerializerGLB::setupMeshRenderer(Entity& entity, const AssetHandle meshHandle, const tinygltf::Mesh& mesh, const AssetRef<Material>& defaultMaterial, const std::vector<AssetHandle>& materials)
    {
        auto& meshRenderer = entity.addComponent<MeshRenderer>();
        meshRenderer.mesh = meshHandle;
        meshRenderer.mesh->apply();

        if (mesh.primitives.empty() || mesh.primitives[0].material < 0)
        {
            meshRenderer.setMaterial(defaultMaterial);
        }
        else
        {
            for (const auto& material : materials)
            {
                meshRenderer.materials.emplace_back(material);
            }
        }
    }

    AssetHandle PrefabSerializerGLB::processMaterial(const tinygltf::Material& material, const tinygltf::Model& model)
    {
        auto mat = std::make_unique<Material>();
        mat->name = material.name.c_str();

        setupPBRProperties(mat.get(), material, model);
        setupTextureProperties(mat.get(), material, model);
        setupMaterialFlags(mat.get(), material);

        return Engine::getAssetManager().addAsset(mat.release());
    }

    void PrefabSerializerGLB::setupPBRProperties(Material* mat, const tinygltf::Material& material, const tinygltf::Model& model)
    {
        const auto& pbr = material.pbrMetallicRoughness;

        if (pbr.baseColorTexture.index >= 0)
        {
            mat->albedoTexture = loadTexture(model.textures[pbr.baseColorTexture.index], model, true);
        }

        const auto& baseColor = pbr.baseColorFactor;
        mat->albedo = glm::vec4(baseColor[0], baseColor[1], baseColor[2], baseColor[3]);

        mat->metalness = static_cast<float>(pbr.metallicFactor);
        mat->roughness = static_cast<float>(pbr.roughnessFactor);

        if (pbr.metallicRoughnessTexture.index >= 0)
        {
            mat->metallicRoughnessTexture = loadTexture(model.textures[pbr.metallicRoughnessTexture.index], model, false);
        }
    }

    void PrefabSerializerGLB::setupTextureProperties(Material* mat, const tinygltf::Material& material, const tinygltf::Model& model)
    {
        if (material.normalTexture.index >= 0)
        {
            mat->normalTextureStrength = static_cast<float>(material.normalTexture.scale);
            mat->normalTexture = loadTexture(model.textures[material.normalTexture.index], model, false);
        }

        if (material.occlusionTexture.index >= 0)
        {
            mat->occlusionTextureStrength = static_cast<float>(material.occlusionTexture.strength);
            mat->occlusionTexture = loadTexture(model.textures[material.occlusionTexture.index], model, false);
        }

        if (material.emissiveTexture.index >= 0)
        {
            mat->emissionTexture = loadTexture(model.textures[material.emissiveTexture.index], model, false);
        }

        const auto& emissive = material.emissiveFactor;
        mat->emission = glm::vec3(emissive[0], emissive[1], emissive[2]);
    }

    void PrefabSerializerGLB::setupMaterialFlags(Material* mat, const tinygltf::Material& material)
    {
        mat->alphaCutoff = static_cast<float>(material.alphaCutoff);
        mat->doubleSided = material.doubleSided;
    }

    TextureFilter convertGLTFFilter(const int gltfFilter)
    {
        switch (gltfFilter)
        {
            case TINYGLTF_TEXTURE_FILTER_NEAREST:
            case TINYGLTF_TEXTURE_FILTER_NEAREST_MIPMAP_NEAREST:
            case TINYGLTF_TEXTURE_FILTER_NEAREST_MIPMAP_LINEAR:
                return TextureFilter::Nearest;
            case TINYGLTF_TEXTURE_FILTER_LINEAR:
            case TINYGLTF_TEXTURE_FILTER_LINEAR_MIPMAP_NEAREST:
            case TINYGLTF_TEXTURE_FILTER_LINEAR_MIPMAP_LINEAR:
            default:
                return TextureFilter::Linear;
        }
    }

    MipmapFilter convertGLTFMipmapFilter(const int gltfFilter)
    {
        switch (gltfFilter)
        {
            case TINYGLTF_TEXTURE_FILTER_NEAREST_MIPMAP_NEAREST:
            case TINYGLTF_TEXTURE_FILTER_LINEAR_MIPMAP_NEAREST:
                return MipmapFilter::Nearest;
            case TINYGLTF_TEXTURE_FILTER_NEAREST_MIPMAP_LINEAR:
            case TINYGLTF_TEXTURE_FILTER_LINEAR_MIPMAP_LINEAR:
                return MipmapFilter::Linear;
            default:
                return MipmapFilter::None;
        }
    }

    TextureWrap convertGLTFWrap(const int gltfWrap)
    {
        switch (gltfWrap)
        {
            case TINYGLTF_TEXTURE_WRAP_MIRRORED_REPEAT:
                return TextureWrap::MirroredRepeat;
            case TINYGLTF_TEXTURE_WRAP_CLAMP_TO_EDGE:
                return TextureWrap::ClampToEdge;
            case TINYGLTF_TEXTURE_WRAP_REPEAT:
            default:
                return TextureWrap::Repeat;
        }
    }

    TextureFormat determineTextureFormat(const tinygltf::Image& image, const bool isSRGB)
    {
        const auto components = image.component;
        const auto bits = image.bits;

        if (components == 1)
        {
            if (bits == 8) return TextureFormat::R8Unorm;
            if (bits == 16) return TextureFormat::R16Unorm;
            if (bits == 32) return TextureFormat::R32Float;
        }
        else if (components == 2)
        {
            if (bits == 8) return TextureFormat::R8G8Unorm;
            if (bits == 16) return TextureFormat::R16G16Unorm;
            if (bits == 32) return TextureFormat::R32G32Float;
        }
        else if (components == 3 || components == 4)
        {
            if (bits == 8) return isSRGB ? TextureFormat::R8G8B8A8UnormSrgb : TextureFormat::R8G8B8A8Unorm;
            if (bits == 16) return TextureFormat::R16G16B16A16Unorm;
            if (bits == 32) return TextureFormat::R32G32B32A32Float;
        }

        return TextureFormat::R8G8B8A8Unorm;
    }

    AssetHandle PrefabSerializerGLB::loadTexture(const tinygltf::Texture& texture, const tinygltf::Model& model, const bool isSrgb)
    {
        if (texture.source < 0)
        {
            return 0;
        }

        const tinygltf::Image& image = model.images[texture.source];

        TextureDescription description{};
        description.format = determineTextureFormat(image, isSrgb);
        description.width = image.width;
        description.height = image.height;

        if (texture.sampler >= 0)
        {
            const tinygltf::Sampler& sampler = model.samplers[texture.sampler];
            description.minFilter = convertGLTFFilter(sampler.minFilter);
            description.magFilter = convertGLTFFilter(sampler.magFilter);
            description.wrapMode.x = convertGLTFWrap(sampler.wrapS);
            description.wrapMode.y = convertGLTFWrap(sampler.wrapT);
        }

        const Ref<Device> device = Engine::getSystem<RenderSystem>()->getDevice();
        const Ref<Texture> tex = device->createTexture(description);

        auto commandList = device->createCommandList();
        commandList->begin();
        device->submit(commandList);

        return Engine::getAssetManager().addAsset(tex.get());
    }

    Mesh* PrefabSerializerGLB::createMesh(const tinygltf::Mesh& mesh, const tinygltf::Model& model)
    {
        if (mesh.primitives.empty())
        {
            return nullptr;
        }

        auto nMesh = std::make_unique<Mesh>();

        for(const auto& primitive : mesh.primitives)
        {

            const auto positions = extractVertexPositions(primitive, model);

            const uint32_t startingVerticesCount = nMesh->vertices.size();

            nMesh->vertices.resize(startingVerticesCount+positions.size());

            for(int i = 0; i < positions.size(); i++)
            {
                nMesh->vertices[startingVerticesCount+i].position = positions[i];
            }

            const auto normals = extractVertexNormals(primitive, model);
            if(normals.size() == positions.size())
            {
                for(int i = 0; i < normals.size(); i++)
                {
                    nMesh->vertices[startingVerticesCount+i].normal = normals[i];
                }
            }

            const auto uvs = extractVertexUVs(primitive, model);
            if(uvs.size() == positions.size())
            {
                for(int i = 0; i < uvs.size(); i++)
                {
                    nMesh->vertices[startingVerticesCount+i].uv = uvs[i];
                }
            }

            auto indices = extractIndices(primitive, model);
            const uint32_t startingIndicesCount = nMesh->indices.size();
            nMesh->indices.resize(startingIndicesCount+indices.size());

            for(int i = 0; i < indices.size(); i++)
            {
                nMesh->indices[startingIndicesCount+i] = startingVerticesCount+indices[i];
            }
        }

        return nMesh.release();
    }

    std::vector<glm::vec3> PrefabSerializerGLB::extractVertexPositions(const tinygltf::Primitive& primitive, const tinygltf::Model& model)
    {
        const auto it = primitive.attributes.find("POSITION");
        if (it == primitive.attributes.end())
        {
            return {};
        }

        const auto& accessor = model.accessors[it->second];
        const auto& bufferView = model.bufferViews[accessor.bufferView];
        const auto& buffer = model.buffers[bufferView.buffer];

        const auto* data = reinterpret_cast<const float*>(buffer.data.data() + bufferView.byteOffset + accessor.byteOffset);

        std::vector<glm::vec3> positions{};
        positions.resize(accessor.count);

        for (size_t i = 0; i < accessor.count; ++i)
        {
            positions[i] = glm::vec3(data[3 * i], data[3 * i + 1], data[3 * i + 2]);
        }

        return positions;
    }

    std::vector<glm::vec3> PrefabSerializerGLB::extractVertexNormals(const tinygltf::Primitive& primitive, const tinygltf::Model& model)
    {
        const auto it = primitive.attributes.find("NORMAL");
        if (it == primitive.attributes.end())
        {
            return {};
        }

        const auto& accessor = model.accessors[it->second];
        const auto& bufferView = model.bufferViews[accessor.bufferView];
        const auto& buffer = model.buffers[bufferView.buffer];

        const auto* data = reinterpret_cast<const float*>(buffer.data.data() + bufferView.byteOffset + accessor.byteOffset);

        std::vector<glm::vec3> normals{};
        normals.resize(accessor.count);

        for (size_t i = 0; i < accessor.count; ++i)
        {
            normals[i] = glm::vec3(data[3 * i], data[3 * i + 1], data[3 * i + 2]);
        }

        return normals;
    }

    std::vector<glm::vec2> PrefabSerializerGLB::extractVertexUVs(const tinygltf::Primitive& primitive, const tinygltf::Model& model)
    {
        const auto it = primitive.attributes.find("TEXCOORD_0");
        if (it == primitive.attributes.end())
        {
            return{};
        }

        const auto& accessor = model.accessors[it->second];
        const auto& bufferView = model.bufferViews[accessor.bufferView];
        const auto& buffer = model.buffers[bufferView.buffer];

        const auto* data = reinterpret_cast<const float*>(buffer.data.data() + bufferView.byteOffset + accessor.byteOffset);

        std::vector<glm::vec2> uvs{};
        uvs.resize(accessor.count);

        for (size_t i = 0; i < accessor.count; ++i)
        {
            uvs[i] = glm::vec2(data[2 * i], data[2 * i + 1]);
        }

        return uvs;
    }

    std::vector<uint32_t> PrefabSerializerGLB::extractIndices(const tinygltf::Primitive& primitive, const tinygltf::Model& model)
    {
        if (primitive.indices < 0)
        {
            return{};
        }

        const auto& accessor = model.accessors[primitive.indices];
        const auto& bufferView = model.bufferViews[accessor.bufferView];
        const auto& buffer = model.buffers[bufferView.buffer];

        std::vector<uint32_t> newIndices{};
        newIndices.resize(accessor.count);

        const auto* data = buffer.data.data() + bufferView.byteOffset + accessor.byteOffset;

        if (accessor.componentType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT)
        {
            const auto* indices = reinterpret_cast<const uint16_t*>(data);
            for (size_t i = 0; i < accessor.count; ++i)
            {
                newIndices[i] = static_cast<uint32_t>(indices[i]);
            }
        }
        else if (accessor.componentType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT)
        {
            const auto* indices = reinterpret_cast<const uint32_t*>(data);
            for (size_t i = 0; i < accessor.count; ++i)
            {
                newIndices[i] = indices[i];
            }
        }

        return newIndices;
    }
}