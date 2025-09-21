#pragma once
#include "assetStream.h"
#include "core/prefab.h"

namespace Neon
{
class AssetSerializer
{
public:
    virtual ~AssetSerializer() = default;

    virtual void serialize(const void* asset, AssetStream* assetStream) = 0;
};
}
