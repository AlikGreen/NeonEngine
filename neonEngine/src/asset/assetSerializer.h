#pragma once
#include "core/prefab.h"

namespace Neon
{
class AssetSerializer
{
public:
    virtual ~AssetSerializer() = default;

    virtual void* load(const std::string& filePath) = 0;
    virtual void serialize(const std::string &filePath) = 0;
    virtual void* deserialize(const std::string &filePath) = 0;
};
}
