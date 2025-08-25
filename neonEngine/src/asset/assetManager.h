#pragma once

#include "assetHandle.h"
#include <filesystem>

#include "assetSerializer.h"
#include "debug/assert.h"

namespace Neon
{
class AssetManager
{
public:
    template<typename T>
    AssetHandle loadAsset(const std::string& filePath)
    {
        const std::filesystem::path fullPath = getFullPath(filePath);

        Assert::check(exists(fullPath), "File was not found\n{}", filePath);

        const std::string fileExtension = fullPath.extension().string();
        if(!serializers.contains(fileExtension)) return 0;

        const auto assetSerializer = serializers.at(fileExtension).get();
        T* asset = static_cast<T*>(assetSerializer->load(fullPath.string()));

        AssetHandle handle = AssetHandle::create();
        assets.emplace(handle, asset);

        return handle;
    }

    template<typename T>
    AssetHandle addAsset(T* asset)
    {
        AssetHandle handle = AssetHandle::create();
        assets.emplace(handle, asset);
        return handle;
    }

    template<typename T>
    T* getAsset(const AssetHandle& assetHandle)
    {
        if(!assetHandle.isValid()) return nullptr;
        return static_cast<T*>(assets.at(assetHandle));
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
    std::unordered_map<AssetHandle, void*> assets;

    static std::string getFullPath(const std::string& filePath);
};
}
