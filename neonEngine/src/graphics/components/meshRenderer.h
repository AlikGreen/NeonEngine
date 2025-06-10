#pragma once
#include "material.h"
#include "asset/assetRef.h"
#include "graphics/mesh.h"

namespace Neon
{
struct MeshRenderer
{
    AssetRef<Material> material = new Material();
    AssetRef<Mesh> mesh{};
};
}
