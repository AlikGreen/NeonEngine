#pragma once

namespace Neon
{
class AssetSerializer
{
public:
    virtual ~AssetSerializer() = default;

    virtual Asset* load(std::string filePath) = 0;
    virtual void serialize(std::string filePath) = 0;
    virtual Asset* deserialize(std::string filePath) = 0;
};
}
