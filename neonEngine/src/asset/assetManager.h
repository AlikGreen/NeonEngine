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

        auto typeIndex = std::type_index(typeid(T));

        Debug::ensure(loaders.contains(typeIndex), "Cannot load object of type {}", typeid(T).name());

        const std::string fileExtension = fullPath.extension().string();
        Debug::ensure(loaders.at(typeIndex).contains(fileExtension), "Cannot load files with {} extension", fileExtension);

        const auto assetLoader = loaders.at(typeIndex).at(fileExtension).get();
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

    template<typename SerializerType, typename AssetType, typename... Args> requires std::derived_from<SerializerType, AssetSerializer>
    void registerSerializer(Args&&... args)
    {
        Ref<SerializerType> serializer = makeRef<SerializerType>(std::forward<Args>(args)...);

        auto typeIndex = std::type_index(typeid(AssetType));
        serializers.emplace(typeIndex, serializer);
    }

    template<typename DeserializerType, typename AssetType, typename... Args> requires std::derived_from<DeserializerType, AssetDeserializer>
    void registerDeserializer(Args&&... args)
    {
        Ref<DeserializerType> deserializer = makeRef<DeserializerType>(std::forward<Args>(args)...);
        auto typeIndex = std::type_index(typeid(AssetType));
        deserializers.emplace(typeIndex, deserializer);
    }

    template<typename LoaderType, typename AssetType, typename... Args> requires std::derived_from<LoaderType, AssetLoader>
    void registerLoader(const std::vector<std::string>& extensions, Args&&... args)
    {
        Ref<LoaderType> loader = makeRef<LoaderType>(std::forward<Args>(args)...);

        auto typeIndex = std::type_index(typeid(AssetType));
        if(!loaders.contains(typeIndex))
            loaders.emplace(typeIndex, std::unordered_map<std::string, Ref<AssetLoader>>());

        for(std::string extension : extensions)
        {
            loaders.at(typeIndex).emplace(extension, loader);
        }
    }
private:
    std::unordered_map<std::type_index, Ref<AssetSerializer>> serializers;
    std::unordered_map<std::type_index, Ref<AssetDeserializer>> deserializers;
    std::unordered_map<std::type_index, std::unordered_map<std::string, Ref<AssetLoader>>> loaders;
    std::unordered_map<AssetHandle, void*> assets;

    static std::string getFullPath(const std::string& filePath);
};
}
