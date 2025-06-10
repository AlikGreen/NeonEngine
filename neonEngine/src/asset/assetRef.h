#pragma once

#include "core/engine.h"

namespace Neon
{
template <typename T>
class AssetRef
{
public:
    AssetRef() : cachedAsset(nullptr), handle(0) {};
    AssetRef(const AssetHandle& handle) : handle(handle) {} // NOLINT(*-explicit-constructor)
    AssetRef(T* asset) : cachedAsset(asset) {} // NOLINT(*-explicit-constructor)

    T* operator->() const
    {
        if (cachedAsset == nullptr)
        {
            cachedAsset = Engine::getAssetManager().getAsset<T>(handle);
        }
        return cachedAsset;
    }

    bool operator==(const AssetHandle& other) const
    {
        if(cachedAsset == nullptr) cachedAsset = Engine::getAssetManager().getAsset<T>(handle);
        return handle == other;
    }

    bool operator!=(const AssetHandle& other) const
    {
        if(cachedAsset == nullptr) cachedAsset = Engine::getAssetManager().getAsset<T>(handle);
        return handle != other;
    }

    bool operator==(const T* other) const
    {
        if(cachedAsset == nullptr) cachedAsset = Engine::getAssetManager().getAsset<T>(handle);
        return cachedAsset == other;
    }

    bool operator!=(const T* other) const
    {
        if(cachedAsset == nullptr) cachedAsset = Engine::getAssetManager().getAsset<T>(handle);
        return cachedAsset != other;
    }
private:
    mutable T* cachedAsset = nullptr;
    AssetHandle handle{};
};
}
