#pragma once
#include "asset/assetImporter.h"

namespace Neon
{
class AudioClipImporter final : public AssetImporter
{
public:
    void* load(const std::string &filepath) override;
};
}
