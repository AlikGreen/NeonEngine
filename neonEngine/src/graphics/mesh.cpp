#include "mesh.h"

#include <tiny_gltf.h>

namespace Neon
{
    void Mesh::apply()
    {
        vertexBuffer = new VertexBuffer(vertices);
    }

    void Mesh::load(const std::string &filePath)
    {
        using namespace tinygltf;

        Model model;
        TinyGLTF loader;
        std::string err, warn;

        // Load the binary glTF (.glb)
        bool ret = loader.LoadBinaryFromFile(&model, &err, &warn, filePath);
        if (!warn.empty())  printf("Warn: %s\n", warn.c_str());
        if (!err.empty())   fprintf(stderr, "Err: %s\n", err.c_str());
        if (!ret)          return;

        // Ensure there is at least one mesh and one primitive
        if (model.meshes.empty())               return;
        const auto& mesh = model.meshes[0];
        if (mesh.primitives.empty())            return;
        const auto& prim = mesh.primitives[0];

        // POSITION
        {
            auto it = prim.attributes.find("POSITION");
            if (it == prim.attributes.end())    return;
            const Accessor& acc = model.accessors[it->second];
            const BufferView& bv = model.bufferViews[acc.bufferView];
            const Buffer& buf = model.buffers[bv.buffer];
            size_t count = acc.count;
            vertices.resize(count);

            const float* dataPtr = reinterpret_cast<const float*>(
                buf.data.data() + bv.byteOffset + acc.byteOffset);

            for (size_t i = 0; i < count; ++i) {
                vertices[i].position = {
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
                const Buffer& buf = model.buffers[bv.buffer];
                const float* dataPtr = reinterpret_cast<const float*>(
                    buf.data.data() + bv.byteOffset + acc.byteOffset);

                for (size_t i = 0; i < acc.count; ++i) {
                    vertices[i].normal = {
                        dataPtr[3 * i + 0],
                        dataPtr[3 * i + 1],
                        dataPtr[3 * i + 2]
                    };
                }
            } else {
                // default normal
                for (auto& v : vertices) v.normal = {0.0f, 0.0f, 0.0f};
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
                    vertices[i].uv = {
                        dataPtr[2 * i + 0],
                        dataPtr[2 * i + 1]
                    };
                }
            } else {
                for (auto& v : vertices) v.uv = {0.0f, 0.0f};
            }
        }

        // --- Extract indices ---
        {
            if (prim.indices < 0) return;
            const Accessor& acc = model.accessors[prim.indices];
            const BufferView& bv = model.bufferViews[acc.bufferView];
            const Buffer& buf = model.buffers[bv.buffer];

            size_t count = acc.count;
            indices.resize(count);

            const unsigned char* data = buf.data.data() + bv.byteOffset + acc.byteOffset;
            // glTF allows index componentType = UNSIGNED_SHORT or UNSIGNED_INT
            if (acc.componentType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT)
            {
                auto ptr = reinterpret_cast<const uint16_t*>(data);
                for (size_t i = 0; i < count; ++i)
                    indices[i] = static_cast<uint32_t>(ptr[i]);
            } else if (acc.componentType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT)
            {
                auto ptr = reinterpret_cast<const uint32_t*>(data);
                for (size_t i = 0; i < count; ++i)
                    indices[i] = ptr[i];
            }
        }
    }

    void Mesh::serialize(AssetStream &stream)
    {
        throw std::runtime_error("Not implemented");
    }

    void Mesh::deserialize(AssetStream &stream)
    {
        throw std::runtime_error("Not implemented");
    }
}
