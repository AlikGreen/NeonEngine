#pragma once

#include "asset.h"
#include "assetHandle.h"
#include <filesystem>

#include "assetSerializer.h"
#include "debug/assert.h"

namespace Neon
{
class AssetManager
{
public:
    template<DerivesAsset T>
    AssetHandle loadAsset(const std::string& filePath)
    {
        const std::filesystem::path fullPath = getFullPath(filePath);

        Assert::check(exists(fullPath), "File was not found\n{}", filePath);

        const std::string fileExtension = fullPath.extension().string();
        if(!serializers.contains(fileExtension)) return 0;

        const auto assetSerializer = serializers.at(fileExtension).get();
        Asset* asset = assetSerializer->load(fullPath.string());

        AssetHandle handle;
        assets.emplace(handle, Scope<Asset>(asset));

        return handle;
    }

    template<DerivesAsset T>
    AssetHandle addAsset(T* asset)
    {
        AssetHandle handle;
        assets.emplace(handle, Scope<Asset>(asset));
        return handle;
    }

    template<DerivesAsset T>
    T* getAsset(const AssetHandle& assetHandle)
    {
        if(!assetHandle.isValid()) return nullptr;
        return dynamic_cast<T*>(assets.at(assetHandle).get());
    }

    template<typename T, typename... Args>
    void registerSerializer(const std::vector<std::string>& extensions, Args&&... args)
    {
        Ref<T> serializer = makeRef<T>(std::forward<Args>(args)...);

        for(std::string extension : extensions)
        {
            serializers.emplace(extension, serializer);
        }
    }
private:
    std::unordered_map<std::string, Ref<AssetSerializer>> serializers;
    std::unordered_map<AssetHandle, Scope<Asset>> assets;

    static std::string getFullPath(const std::string& filePath);
};
}
