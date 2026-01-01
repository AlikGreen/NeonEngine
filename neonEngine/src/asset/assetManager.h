#pragma once

#include <filesystem>

#include "assetDeserializer.h"
#include "assetLoader.h"
#include "assetSerializer.h"
#include "debug.h"
#include "log.h"

namespace Neon
{

struct AssetMetadata
{
    std::string name;
    std::type_index type;
    std::filesystem::path physicalPath;
};

using AssetID = uint64_t;

template<typename T>
class AssetRef;

class AssetManager
{
public:
    template<typename T>
    AssetRef<T> loadAsset(const std::string& filepath, std::string name = "");
    template<typename T> // requires (!std::is_const_v<T>)
    AssetRef<T> addAsset(T* asset, std::string name = "");
    template<typename T>
    AssetRef<T> addAsset(T asset, std::string name = "");

    template<typename T>
    T& getAsset(const AssetID assetHandle)
    {
        Debug::ensure(isValid(assetHandle), "Tried to get an asset that did not exist.");
        return *static_cast<T*>(assets.at(assetHandle));
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

    std::vector<AssetID> getAllAssetIDs();
    AssetMetadata getMetadata(AssetID handle);
    uint32_t generateID();
    bool isValid(AssetID id) const;

    static std::string getFullPath(const std::string& filePath);
private:
    AssetID nextHandle = 1;

    std::unordered_map<std::type_index, Box<AssetSerializer>> serializers;
    std::unordered_map<std::type_index, Box<AssetDeserializer>> deserializers;
    std::unordered_map<std::type_index, std::unordered_map<std::string, Rc<AssetLoader>>> loaders;

    std::vector<AssetID> assetHandles;
    std::unordered_map<std::string, AssetID> pathAssetMap;
    std::unordered_map<AssetID, void*> assets;
    std::unordered_map<AssetID, AssetMetadata> assetsMetadata;
};
}