#pragma once

#include "assetHandle.h"
#include <filesystem>

#include "assetDeserializer.h"
#include "assetLoader.h"
#include "assetSerializer.h"
#include "debug.h"
#include "log.h"

namespace Neon
{
class AssetManager
{
public:
    template<typename T>
    AssetHandle loadAsset(const std::string& filePath)
    {
        const std::filesystem::path fullPath = getFullPath(filePath);

        Debug::ensure(exists(fullPath), "File was not found\n{}", filePath);

        const std::string fileExtension = fullPath.extension().string();
        Debug::ensure(loaders.contains(fileExtension), "Cannot load files with {} extension", fileExtension);

        const auto assetLoader = loaders.at(fileExtension).get();
        T* asset = static_cast<T*>(assetLoader->load(fullPath.string()));

        AssetHandle handle = AssetHandle::create();
        assets.emplace(handle, asset);

        return handle;
    }

    template<typename T> requires (!std::is_const_v<T>)
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

    template<typename T, typename... Args> requires std::derived_from<T, AssetSerializer>
    void registerSerializer(const std::vector<std::string>& extensions, Args&&... args)
    {
        Ref<T> serializer = makeRef<T>(std::forward<Args>(args)...);

        for(std::string extension : extensions)
        {
            serializers.emplace(extension, serializer);
        }
    }

    template<typename T, typename... Args> requires std::derived_from<T, AssetDeserializer>
    void registerDeserializer(const std::vector<std::string>& extensions, Args&&... args)
    {
        Ref<T> deserializer = makeRef<T>(std::forward<Args>(args)...);

        for(std::string extension : extensions)
        {
            deserializers.emplace(extension, deserializer);
        }
    }

    template<typename T, typename... Args> requires std::derived_from<T, AssetLoader>
    void registerLoader(const std::vector<std::string>& extensions, Args&&... args)
    {
        Ref<T> loader = makeRef<T>(std::forward<Args>(args)...);

        for(std::string extension : extensions)
        {
            loaders.emplace(extension, loader);
        }
    }
private:
    std::unordered_map<std::string, Ref<AssetSerializer>> serializers;
    std::unordered_map<std::string, Ref<AssetDeserializer>> deserializers;
    std::unordered_map<std::string, Ref<AssetLoader>> loaders;
    std::unordered_map<AssetHandle, void*> assets;

    static std::string getFullPath(const std::string& filePath);
};
}
