#pragma once
#include "miniaudio.h"
#include "asset/asset.h"

namespace Neon
{
class AudioClip final : public Asset
{
public:

private:
   friend class AudioManager;
   ma_decoder decoder = {};
};
}
