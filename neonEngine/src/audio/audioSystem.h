#pragma once
#include <unordered_map>

#include "audioClip.h"
#include "sound.h"
#include "asset/assetRef.h"
#include "core/system.h"

namespace Neon
{
class AudioSystem final : public System
{
public:
    void postUpdate() override;
private:
    std::unordered_map<AssetID, Sound> sounds;
};
}
