#pragma once
#include "core/prefab.h"

namespace Neon
{
class AssetSerializer
{
public:
    virtual ~AssetSerializer() = default;

    virtual Asset* load(const std::string& filePath) = 0;
    virtual void serialize(const std::string &filePath) = 0;
    virtual Asset* deserialize(const std::string &filePath) = 0;
};
}
