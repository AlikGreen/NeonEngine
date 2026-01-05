#pragma once
#include <istream>
#include <ostream>

#include "assetID.h"
#include "core/prefab.h"

namespace Neon
{
class AssetSerializer
{
public:
    virtual ~AssetSerializer() = default;

    virtual void serialize(const void* asset, std::ostream& assetStream) = 0;
    virtual void* deserialize(std::istream& assetStream) = 0;
};

inline std::ostream& operator<<(std::ostream& os, const AssetID asset)
{
    os << asset.getId();
    return os;
}

inline std::istream& operator>>(std::istream& is, AssetID& asset)
{
    uint64_t id;
    is >> id;
    asset = AssetID(id);
    return is;
}
}
