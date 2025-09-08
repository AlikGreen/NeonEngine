#pragma once
#include "asset/assetSerializer.h"

namespace Neon
{
class ImageSerializer final : AssetSerializer
{
public:
    void* load(const std::string& filePath) override;
    void serialize(const std::string &filePath) override;
    void* deserialize(const std::string &filePath) override;
};
}
