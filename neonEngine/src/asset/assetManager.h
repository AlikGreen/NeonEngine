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
    AssetHandle loadAsset(const std::string& filepath, std::string name = "")
    {
        const std::filesystem::path fullPath = getFullPath(filepath);
        if(pathAssetMap.contains(fullPath.string()))
            return pathAssetMap.at(fullPath.string());

        Debug::ensure(exists(fullPath), "File was not found\n{}", filepath);

        if(name.empty())
        {
            name = fullPath.stem().string();
        }
        const auto typeIndex = std::type_index(typeid(T));

        Debug::ensure(loaders.contains(typeIndex), "Cannot load object of type {}", typeid(T).name());

        const std::string fileExtension = fullPath.extension().string();
        Debug::ensure(loaders.at(typeIndex).contains(fileExtension), "Cannot load files with {} extension", fileExtension);

        const auto assetLoader = loaders.at(typeIndex).at(fileExtension).get();
        void* asset = assetLoader->load(fullPath.string());

        AssetHandle handle = AssetHandle::create();
        assets.emplace(handle, AssetContainer { asset, typeIndex, name });
        assetHandles.push_back(handle);
        pathAssetMap.emplace(fullPath.string(), handle);

        return handle;
    }

    template<typename T> // requires (!std::is_const_v<T>)
    AssetHandle addAsset(T* asset, std::string name = "")
    {
        const auto typeIndex = std::type_index(typeid(T));

        if(name.empty())
        {
            name = typeIndex.name();
        }

        AssetHandle handle = AssetHandle::create();
        assets.emplace(handle, AssetContainer { asset, typeIndex, name});
        assetHandles.push_back(handle);
        return handle;
    }

    template<typename T>
    AssetHandle addAsset(T asset, std::string name = "")
    {
        const auto typeIndex = std::type_index(typeid(T));

        if(name.empty())
        {
            name = typeIndex.name();
        }

        AssetHandle handle = AssetHandle::create();
        T* heapAsset = new T(std::move(asset));  // Allocate on heap
        assets.emplace(handle, AssetContainer { heapAsset, typeIndex, name});
        assetHandles.push_back(handle);
        return handle;
    }

    template<typename T>
    T& getAsset(const AssetHandle& assetHandle)
    {
        Debug::ensure(assetHandle.isValid(), "Tried to get an asset that did not exist.");
        return *static_cast<T*>(assets.at(assetHandle).asset);
    }

    template<typename SerializerType, typename AssetType, typename... Args> requires std::derived_from<SerializerType, AssetSerializer>
    void registerSerializer(Args&&... args)
    {
        Box<SerializerType> serializer = makeBox<SerializerType>(std::forward<Args>(args)...);

        auto typeIndex = std::type_index(typeid(AssetType));
        serializers.emplace(typeIndex, serializer);
    }

    template<typename DeserializerType, typename AssetType, typename... Args> requires std::derived_from<DeserializerType, AssetDeserializer>
    void registerDeserializer(Args&&... args)
    {
        Box<DeserializerType> deserializer = makeBox<DeserializerType>(std::forward<Args>(args)...);
        auto typeIndex = std::type_index(typeid(AssetType));
        deserializers.emplace(typeIndex, deserializer);
    }

    template<typename LoaderType, typename AssetType, typename... Args> requires std::derived_from<LoaderType, AssetLoader>
    void registerLoader(const std::vector<std::string>& extensions, Args&&... args)
    {
        Rc<LoaderType> loader = makeBox<LoaderType>(std::forward<Args>(args)...);

        auto typeIndex = std::type_index(typeid(AssetType));
        if(!loaders.contains(typeIndex))
            loaders.emplace(typeIndex, std::unordered_map<std::string, Rc<AssetLoader>>());

        for(std::string extension : extensions)
        {
            loaders.at(typeIndex).emplace(extension, loader);
        }
    }

    std::vector<AssetHandle> getAllAssetHandles();
    std::string getName(AssetHandle handle);
    std::type_index getType(AssetHandle handle) const;

    static std::string getFullPath(const std::string& filePath);
private:
    struct AssetContainer
    {
        void* asset;
        std::type_index type;
        std::string name;
    };

    std::unordered_map<std::type_index, Box<AssetSerializer>> serializers;
    std::unordered_map<std::type_index, Box<AssetDeserializer>> deserializers;
    std::unordered_map<std::type_index, std::unordered_map<std::string, Rc<AssetLoader>>> loaders;
    std::vector<AssetHandle> assetHandles;
    std::unordered_map<std::string, AssetHandle> pathAssetMap;
    std::unordered_map<AssetHandle, AssetContainer> assets;
};
}
