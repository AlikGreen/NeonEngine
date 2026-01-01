#pragma once

#include "assetManager.h"
#include "core/engine.h"

namespace Neon
{
template <typename T>
class AssetRef
{
public:
    AssetRef() : cachedAsset(nullptr), id(0)         {  };
    AssetRef(AssetID id) : cachedAsset(nullptr), id(id) {  };
    AssetRef(T* asset) : cachedAsset(asset)      {  } // NOLINT(*-explicit-constructor)

    T* operator->() const
    {
        updateCachedAsset();
        return cachedAsset;
    }

    T& operator*() const
    {
        updateCachedAsset();
        return *cachedAsset;
    }

    T& get() const
    {
        updateCachedAsset();
        return *cachedAsset;
    }

    AssetID getID() const
    {
        return id;
    }

    bool operator==(const AssetRef other) const
    {
        return id == other.id;
    }

    bool operator!=(const AssetRef other) const
    {
        return id != other.id;
    }

    operator bool() const
    {
        return id != 0;
    }
private:
    friend class AssetManager;
    void updateCachedAsset() const
    {
        AssetManager& assetManger = Engine::getAssetManager();
        if (cachedAsset == nullptr && assetManger.isValid(id))
        {
            cachedAsset = &assetManger.getAsset<T>(id);
        }
    }

    mutable T* cachedAsset = nullptr;
    AssetID id{};
};

template<typename T> // requires (!std::is_const_v<T>)
AssetRef<T> AssetManager::addAsset(T* asset, std::string name)
{
    const auto typeIndex = std::type_index(typeid(T));

    if(name.empty())
    {
        name = typeIndex.name();
    }

    AssetID handle = generateID();
    assets.emplace(handle, asset);
    assetsMetadata.emplace(handle, AssetMetadata { name, typeIndex, "" });

    assetHandles.push_back(handle);
    return handle;
}

template<typename T>
AssetRef<T> AssetManager::addAsset(T asset, std::string name)
{
    const auto typeIndex = std::type_index(typeid(T));

    if(name.empty())
    {
        name = typeIndex.name();
    }

    AssetID handle = generateID();
    T* heapAsset = new T(std::move(asset));  // Allocate on heap
    assets.emplace(handle, heapAsset);
    assetsMetadata.emplace(handle, AssetMetadata { name, typeIndex, "" });

    assetHandles.push_back(handle);
    return handle;
}

template<typename T>
AssetRef<T> AssetManager::loadAsset(const std::string& filepath, std::string name)
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

    AssetID handle = generateID();
    assets.emplace(handle, asset);
    assetsMetadata.emplace(handle, AssetMetadata { name, typeIndex, fullPath });
    assetHandles.push_back(handle);
    pathAssetMap.emplace(fullPath.string(), handle);

    return handle;
}
}
