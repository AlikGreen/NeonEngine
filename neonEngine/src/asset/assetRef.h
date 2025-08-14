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
    AssetRef(T* asset) : cachedAsset(Ref<T>(asset))      {  } // NOLINT(*-explicit-constructor)
    AssetRef(Ref<T> asset) : cachedAsset(asset)          {  } // NOLINT(*-explicit-constructor)

    T* operator->() const
    {
        updateCachedAsset();
        return cachedAsset.get();
    }

    T& operator*() const
    {
        updateCachedAsset();
        return *cachedAsset.get();
    }

    Ref<T> get() const
    {
        updateCachedAsset();
        return cachedAsset;
    }

    T* raw() const
    {
        updateCachedAsset();
        return cachedAsset.get();
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
        return cachedAsset.get() == other;
    }

    bool operator!=(const T* other) const
    {
        updateCachedAsset();
        return cachedAsset.get() != other;
    }
private:
    void updateCachedAsset() const
    {
        if(cachedAsset == nullptr) cachedAsset = Engine::getAssetManager().getAsset<T>(handle);
    }

    mutable Ref<T> cachedAsset = nullptr;
    AssetHandle handle{};
};
}
