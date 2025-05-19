#pragma once
#include <unordered_set>

#include "asset.h"

namespace Neon
{
class AssetManager
{
public:
    template<DerivesAsset T>
    Ref<T> loadAsset(const std::string& filePath)
    {
        Ref<Asset> asset = makeRef<T>();
        asset->load(filePath);

        assets.insert(asset);

        return asset;
    }
private:
    std::unordered_set<Ref<Asset>> assets;
};
}
