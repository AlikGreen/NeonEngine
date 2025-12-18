#pragma once

#include "assetHandle.h"
#include "assetManager.h"
#include "core/engine.h"

namespace Neon
{
template <typename T>
class AssetRef
{
public:
    AssetRef() : cachedAsset(nullptr), handle(0)         {  };
    AssetRef(const AssetHandle& handle) : handle(handle) {  } // NOLINT(*-explicit-constructor)
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

    AssetHandle getHandle() const
    {
        return handle;
    }

    bool operator==(const AssetHandle& other) const
    {
        updateCachedAsset();
        return handle == other;
    }

    bool operator!=(const AssetHandle& other) const
    {
        updateCachedAsset();
        return handle != other;
    }

    bool operator==(const T* other) const
    {
        updateCachedAsset();
        return cachedAsset == other;
    }

    bool operator!=(const T* other) const
    {
        updateCachedAsset();
        return cachedAsset != other;
    }
private:
    friend class AssetManager;
    void updateCachedAsset() const
    {
        if (cachedAsset == nullptr && handle.isValid())
        {
            cachedAsset = &Engine::getAssetManager().getAsset<T>(handle);
        }
    }

    mutable T* cachedAsset = nullptr;
    AssetHandle handle{};
};
}
