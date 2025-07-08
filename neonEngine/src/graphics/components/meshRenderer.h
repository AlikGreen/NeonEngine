#pragma once
#include "material.h"
#include "asset/assetRef.h"
#include "graphics/mesh.h"

namespace Neon
{
struct MeshRenderer
{
    std::vector<AssetRef<Material>> materials{};
    AssetRef<Mesh> mesh{};

    void setMaterial(const AssetRef<Material> material)
    {
        if(materials.empty())
            materials.push_back(material);
        else
            materials[0] = material;
    }

    AssetRef<Material> getMaterial() const
    {
        if(materials.empty()) return nullptr;
        return materials[0];
    }
};
}
