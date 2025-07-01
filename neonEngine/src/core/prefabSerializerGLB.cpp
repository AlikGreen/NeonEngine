#include "prefabSerializerGLB.h"

#include <tiny_gltf.h>

#include "graphics/components/meshRenderer.h"
#include "core/engine.h"

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

        for(const auto& node : model.nodes)
        {
            if(node.mesh >= 0)
            {
                Mesh* nMesh = createMesh(model.meshes[node.mesh], model);
                if(nMesh == nullptr) continue;
                const auto meshHandle = Engine::getAssetManager().addAsset(nMesh);
                Entity entity = nModel->world.createEntity();
                entity.setParent(rootEntity);
                auto& meshRenderer = entity.addComponent<MeshRenderer>();
                meshRenderer.mesh = meshHandle;
                meshRenderer.mesh->apply();

                meshRenderer.material = new Material();
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

    Mesh* PrefabSerializerGLB::createMesh(const tinygltf::Mesh &mesh, const tinygltf::Model &model)
    {
        using namespace tinygltf;

        auto nMesh = new Mesh();

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

