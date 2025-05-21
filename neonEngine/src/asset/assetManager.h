#pragma once

#include "asset.h"
#include "assetHandle.h"
#include <filesystem>

namespace Neon
{
class AssetManager
{
public:
    template<DerivesAsset T>
    static AssetHandle loadAsset(const std::string& filePath)
    {
        const std::filesystem::path fullPath = getFullPath(filePath);

        Ref<Asset> asset = makeRef<T>();
        asset->load(fullPath.string());

        AssetHandle handle;
        assets.emplace(handle, asset);

        return handle;
    }

    template<DerivesAsset T>
    static Ref<T> getAsset(const AssetHandle& assetHandle)
    {
        return std::static_pointer_cast<T>(assets.at(assetHandle));
    }
private:
    static std::unordered_map<AssetHandle, Ref<Asset>> assets;

    static std::string getFullPath(const std::string& filePath);
};
}
