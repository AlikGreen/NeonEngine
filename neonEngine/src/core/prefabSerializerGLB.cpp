#include "prefabSerializerGLB.h"

#include <tiny_gltf.h>

#include "graphics/components/meshRenderer.h"
#include "core/engine.h"
#include "graphics/renderSystem.h"
#include "graphics/api/texture.h"

namespace Neon
{
    Prefab* PrefabSerializerGLB::load(const std::string filePath)
    {
        tinygltf::Model model;
        tinygltf::TinyGLTF loader;
        std::string err, warn;

        const auto nModel = new Prefab();

        const bool ret = loader.LoadBinaryFromFile(&model, &err, &warn, filePath);
        if (!warn.empty())  printf("Warn: %s\n", warn.c_str());
        if (!err.empty())   fprintf(stderr, "Err: %s\n", err.c_str());
        if (!ret)          return nullptr;

        Entity rootEntity = nModel->world.createEntity();
        rootEntity.addComponent<PrefabComponent>();

        std::vector<AssetHandle> materials{};


        for (const auto& material : model.materials)
        {
            materials.push_back(processMaterial(material, model));
        }

        AssetRef<Material> defaultMat = Engine::getAssetManager().addAsset(new Material());

        for(const auto& node : model.nodes)
        {
            if(node.mesh >= 0)
            {
                const tinygltf::Mesh& mesh = model.meshes[node.mesh];
                Mesh* nMesh = createMesh(mesh, model);
                if(nMesh == nullptr) continue;
                const auto meshHandle = Engine::getAssetManager().addAsset(nMesh);
                Entity entity = nModel->world.createEntity();
                entity.setParent(rootEntity);
                auto& meshRenderer = entity.addComponent<MeshRenderer>();
                meshRenderer.mesh = meshHandle;
                meshRenderer.mesh->apply();

                if(mesh.primitives[0].material < 0)
                {
                    meshRenderer.setMaterial(defaultMat);
                }else
                {
                    // TODO make primatives have diffrent materials
                    meshRenderer.setMaterial(materials[mesh.primitives[0].material]);
                }
            }
        }

        return nModel;
    }

    void PrefabSerializerGLB::serialize(std::string filePath)
    {
    }

    Prefab* PrefabSerializerGLB::deserialize(std::string filePath)
    {
        return nullptr;
    }

    AssetHandle PrefabSerializerGLB::processMaterial(const tinygltf::Material& material, const tinygltf::Model& model)
    {
        auto* mat = new Material();
        mat->name = material.name.c_str();

        if (material.pbrMetallicRoughness.baseColorTexture.index >= 0)
        {
            const int textureIndex = material.pbrMetallicRoughness.baseColorTexture.index;
            mat->albedoTexture = loadTexture(model.textures[textureIndex], model, true);
        }
        const auto baseColorFactor = material.pbrMetallicRoughness.baseColorFactor;
        mat->albedo.r = static_cast<float>(baseColorFactor[0]);
        mat->albedo.g = static_cast<float>(baseColorFactor[1]);
        mat->albedo.b = static_cast<float>(baseColorFactor[2]);
        mat->albedo.a = static_cast<float>(baseColorFactor[3]);

        mat->metalness = static_cast<float>(material.pbrMetallicRoughness.metallicFactor);
        mat->roughness = static_cast<float>(material.pbrMetallicRoughness.roughnessFactor);

        if (material.pbrMetallicRoughness.metallicRoughnessTexture.index >= 0)
        {
            const int textureIndex = material.pbrMetallicRoughness.metallicRoughnessTexture.index;
            mat->metallicRoughnessTexture = loadTexture(model.textures[textureIndex], model, false);
        }

        if (material.normalTexture.index >= 0)
        {
            const int textureIndex = material.normalTexture.index;
            mat->normalTextureStrength = static_cast<float>(material.normalTexture.scale);
            mat->normalTexture = loadTexture(model.textures[textureIndex], model, false);
        }

        if (material.occlusionTexture.index >= 0)
        {
            const int textureIndex = material.occlusionTexture.index;
            mat->occlusionTextureStrength = static_cast<float>(material.occlusionTexture.strength);
            mat->occlusionTexture = loadTexture(model.textures[textureIndex], model, false);
        }

        if (material.emissiveTexture.index >= 0)
        {
            const int textureIndex = material.emissiveTexture.index;
            mat->emissionTexture = loadTexture(model.textures[textureIndex], model, false);
        }

        auto emissiveFactor = material.emissiveFactor;
        mat->emission.r = static_cast<float>(emissiveFactor[0]);
        mat->emission.g = static_cast<float>(emissiveFactor[1]);
        mat->emission.b = static_cast<float>(emissiveFactor[2]);

        std::string alphaMode = material.alphaMode;
        mat->alphaCutoff = static_cast<float>(material.alphaCutoff);

        mat->doubleSided = material.doubleSided;

        return Engine::getAssetManager().addAsset(mat);
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

    // Helper function to convert glTF mipmap filter to your MipmapFilter enum
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
            case TINYGLTF_TEXTURE_FILTER_NEAREST:
            case TINYGLTF_TEXTURE_FILTER_LINEAR:
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

    TextureFormat determineTextureFormat(const tinygltf::Image& image, const bool isSRGB = false)
    {
        if (image.component == 1)
        {
            if (image.bits == 8)
                return TextureFormat::R8Unorm;
            if (image.bits == 16)
                return TextureFormat::R16Unorm;
            if (image.bits == 32)
                return TextureFormat::R32Float;
        }
        if (image.component == 2)
        {
            if (image.bits == 8)
                return TextureFormat::R8G8Unorm;
            if (image.bits == 16)
                return TextureFormat::R16G16Unorm;
            if (image.bits == 32)
                return TextureFormat::R32G32Float;
        }
        if (image.component == 3)
        {
            if (image.bits == 8)
                return isSRGB ? TextureFormat::R8G8B8A8UnormSrgb : TextureFormat::R8G8B8A8Unorm;
            if (image.bits == 16)
                return TextureFormat::R16G16B16A16Unorm;
            if (image.bits == 32)
                return TextureFormat::R32G32B32A32Float;
        }
        if (image.component == 4)
        {
            if (image.bits == 8)
                return isSRGB ? TextureFormat::R8G8B8A8UnormSrgb : TextureFormat::R8G8B8A8Unorm;
            if (image.bits == 16)
                return TextureFormat::R16G16B16A16Unorm;
            if (image.bits == 32)
                return TextureFormat::R32G32B32A32Float;
        }

        return TextureFormat::R8G8B8A8Unorm;
    }

    AssetHandle PrefabSerializerGLB::loadTexture(const tinygltf::Texture& texture, const tinygltf::Model& model, const bool isSrgb)
    {
        if (texture.source < 0) return 0;

        TextureDescription description{};

        const tinygltf::Image& image = model.images[texture.source];
        description.format = determineTextureFormat(image, isSrgb);

        description.width = image.width;
        description.height = image.height;

        // Sampler settings
        if (texture.sampler >= 0)
        {
            const tinygltf::Sampler& sampler = model.samplers[texture.sampler];

            description.minFilter = convertGLTFFilter(sampler.minFilter);
            description.magFilter = convertGLTFFilter(sampler.magFilter);
            description.wrapMode.x = convertGLTFWrap(sampler.wrapS);
            description.wrapMode.y = convertGLTFWrap(sampler.wrapT);
        }

        const unsigned char* data = image.image.data();
        // SUASFDYUADU set texture data OIFHSFBSIAI

        const Ref<Texture> tex = Engine::getSystem<RenderSystem>()->getDevice()->createTexture(description);
        return Engine::getAssetManager().addAsset(tex.get());
    }

    Mesh* PrefabSerializerGLB::createMesh(const tinygltf::Mesh &mesh, const tinygltf::Model &model)
    {
        using namespace tinygltf;

        const auto nMesh = new Mesh();

        if (mesh.primitives.empty())            return nullptr;
        const auto& prim = mesh.primitives[0];

        // POSITION
        {
            const auto it = prim.attributes.find("POSITION");
            if (it == prim.attributes.end())    return nullptr;
            const Accessor& acc = model.accessors[it->second];
            const BufferView& bv = model.bufferViews[acc.bufferView];
            const tinygltf::Buffer& buf = model.buffers[bv.buffer];
            const size_t count = acc.count;
            nMesh->vertices.resize(count);

            const auto* dataPtr = reinterpret_cast<const float*>(
                buf.data.data() + bv.byteOffset + acc.byteOffset);

            for (size_t i = 0; i < count; ++i) {
                nMesh->vertices[i].position = {
                    dataPtr[3 * i + 0],
                    dataPtr[3 * i + 1],
                    dataPtr[3 * i + 2]
                };
            }
        }


        // NORMAL (optional)
        {
            const auto it = prim.attributes.find("NORMAL");
            if (it != prim.attributes.end()) {
                const Accessor& acc = model.accessors[it->second];
                const BufferView& bv = model.bufferViews[acc.bufferView];
                const tinygltf::Buffer& buf = model.buffers[bv.buffer];
                const auto* dataPtr = reinterpret_cast<const float*>(
                    buf.data.data() + bv.byteOffset + acc.byteOffset);

                for (size_t i = 0; i < acc.count; ++i) {
                    nMesh->vertices[i].normal = {
                        dataPtr[3 * i + 0],
                        dataPtr[3 * i + 1],
                        dataPtr[3 * i + 2]
                    };
                }
            } else {
                // default normal
                for (auto& v : nMesh->vertices) v.normal = {0.0f, 0.0f, 0.0f};
            }
        }

        // TEXCOORD_0 (optional)
        {
            auto it = prim.attributes.find("TEXCOORD_0");
            if (it != prim.attributes.end()) {
                const tinygltf::Accessor& acc = model.accessors[it->second];
                const tinygltf::BufferView& bv = model.bufferViews[acc.bufferView];
                const tinygltf::Buffer& buf = model.buffers[bv.buffer];
                const auto* dataPtr = reinterpret_cast<const float*>(
                    buf.data.data() + bv.byteOffset + acc.byteOffset);

                for (size_t i = 0; i < acc.count; ++i) {
                    nMesh->vertices[i].uv = {
                        dataPtr[2 * i + 0],
                        dataPtr[2 * i + 1]
                    };
                }
            } else {
                for (auto& v : nMesh->vertices) v.uv = {0.0f, 0.0f};
            }
        }

        // --- Extract indices ---
        {
            if (prim.indices < 0) return nullptr;
            const Accessor& acc = model.accessors[prim.indices];
            const BufferView& bv = model.bufferViews[acc.bufferView];
            const tinygltf::Buffer& buf = model.buffers[bv.buffer];

            const size_t count = acc.count;
            nMesh->indices.resize(count);

            const unsigned char* data = buf.data.data() + bv.byteOffset + acc.byteOffset;
            // glTF allows index componentType = UNSIGNED_SHORT or UNSIGNED_INT
            if (acc.componentType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT)
            {
                const auto ptr = reinterpret_cast<const uint16_t*>(data);
                for (size_t i = 0; i < count; ++i)
                    nMesh->indices[i] = static_cast<uint32_t>(ptr[i]);
            } else if (acc.componentType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT)
            {
                const auto ptr = reinterpret_cast<const uint32_t*>(data);
                for (size_t i = 0; i < count; ++i)
                    nMesh->indices[i] = ptr[i];
            }
        }
        return nMesh;
    }
}

