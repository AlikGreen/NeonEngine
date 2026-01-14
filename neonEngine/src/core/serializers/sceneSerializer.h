#pragma once
#include "asset/assetSerializer.h"

namespace Neon
{
class SceneSerializer final : public AssetSerializer
{
public:
    void serialize(AssetStream &assetStream, AssetManager &assetManager, void *asset) override;
    void* deserialize(AssetStream &assetStream, AssetManager &assetManager) override;
};
}
