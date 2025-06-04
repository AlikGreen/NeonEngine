#pragma once
#include "miniaudio.h"
#include "asset/asset.h"

namespace Neon
{
class AudioClip final : public Asset
{
public:
   void load(const std::string& filePath) override;
   void serialize(AssetStream &stream) override;
   void deserialize(AssetStream &stream) override;

private:
   friend class AudioManager;
   ma_decoder decoder = {};
};
}
