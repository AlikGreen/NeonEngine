#pragma once

#include "assetManager.h"
#include "core/engine.h"

namespace Neon
{
template <typename T>
class AssetRef
{
public:
    AssetRef() : assetManager(nullptr), cachedAsset(nullptr), id(0) {  };
    AssetRef(std::nullptr_t) : assetManager(nullptr), cachedAsset(nullptr), id(0) { }

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
        return id.isValid();
    }
private:
    friend class AssetManager;

    AssetRef(AssetManager* assetManager, const AssetID id) : assetManager(assetManager), cachedAsset(nullptr), id(id) {  };
    AssetRef(AssetManager* assetManager, T* asset) : assetManager(assetManager), cachedAsset(asset)      {  } // NOLINT(*-explicit-constructor)

    void updateCachedAsset() const
    {
        if (cachedAsset == nullptr && assetManager != nullptr && assetManager->isValid(id))
        {
            cachedAsset = &assetManager->getAssetRef<T>(id);
        }
    }

    AssetManager* assetManager;
    mutable T* cachedAsset = nullptr;
    AssetID id{};
};

template<typename T>
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
    return AssetRef<T>(this, handle);
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
    return AssetRef<T>(this, handle);
}

template<typename T>
AssetRef<T> AssetManager::import(const std::string& filepath)
{
    const std::filesystem::path fullPath = getFullPath(filepath);

    Debug::ensure(exists(fullPath), "File was not found\n{}", filepath);

    const auto typeIndex = std::type_index(typeid(T));

    Debug::ensure(importers.contains(typeIndex), "Cannot load object of type {}", typeid(T).name());

    const std::string name = fullPath.stem().string();
    const auto assetLoader = importers.at(typeIndex).get();
    T* asset = static_cast<T*>(assetLoader->load(fullPath.string()));

    AssetID handle = generateID();
    assets.emplace(handle, asset);
    assetsMetadata.emplace(handle, AssetMetadata { name, typeIndex, filepath });

    assetHandles.push_back(handle);
    return AssetRef<T>(this, handle);
}

template<typename T>
AssetRef<T> AssetManager::getAsset(const AssetID assetHandle)
{
    Debug::ensure(isValid(assetHandle), "Tried to get an asset that did not exist.");
    return AssetRef<T>(this, static_cast<T*>(assets.at(assetHandle)));
}
}
