#include "MeshSerializerGLB.h"

#include <tiny_gltf.h>

namespace Neon
{
    Mesh* MeshSerializerGLB::load(const std::string filePath)
    {
        using namespace tinygltf;

        const auto nMesh = new Mesh();

        Model model;
        TinyGLTF loader;
        std::string err, warn;

        // Load the binary glTF (.glb)
        const bool ret = loader.LoadBinaryFromFile(&model, &err, &warn, filePath);
        if (!warn.empty())  printf("Warn: %s\n", warn.c_str());
        if (!err.empty())   fprintf(stderr, "Err: %s\n", err.c_str());
        if (!ret)          return nullptr;

        // Ensure there is at least one mesh and one primitive
        if (model.meshes.empty())               return nullptr;
        const auto& mesh = model.meshes[0];
        if (mesh.primitives.empty())            return nullptr;
        const auto& prim = mesh.primitives[0];

        // POSITION
        {
            auto it = prim.attributes.find("POSITION");
            if (it == prim.attributes.end())    return nullptr;
            const Accessor& acc = model.accessors[it->second];
            const BufferView& bv = model.bufferViews[acc.bufferView];
            const tinygltf::Buffer& buf = model.buffers[bv.buffer];
            size_t count = acc.count;
            nMesh->vertices.resize(count);

            const float* dataPtr = reinterpret_cast<const float*>(
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
            auto it = prim.attributes.find("NORMAL");
            if (it != prim.attributes.end()) {
                const Accessor& acc = model.accessors[it->second];
                const BufferView& bv = model.bufferViews[acc.bufferView];
                const tinygltf::Buffer& buf = model.buffers[bv.buffer];
                const float* dataPtr = reinterpret_cast<const float*>(
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
                const float* dataPtr = reinterpret_cast<const float*>(
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

            size_t count = acc.count;
            nMesh->indices.resize(count);

            const unsigned char* data = buf.data.data() + bv.byteOffset + acc.byteOffset;
            // glTF allows index componentType = UNSIGNED_SHORT or UNSIGNED_INT
            if (acc.componentType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT)
            {
                auto ptr = reinterpret_cast<const uint16_t*>(data);
                for (size_t i = 0; i < count; ++i)
                    nMesh->indices[i] = static_cast<uint32_t>(ptr[i]);
            } else if (acc.componentType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT)
            {
                auto ptr = reinterpret_cast<const uint32_t*>(data);
                for (size_t i = 0; i < count; ++i)
                    nMesh->indices[i] = ptr[i];
            }
        }

        nMesh->apply();
        return nMesh;
    }

    void MeshSerializerGLB::serialize(std::string filePath)
    {
    }

    Mesh * MeshSerializerGLB::deserialize(std::string filePath)
    {
        return nullptr;
    }
}

