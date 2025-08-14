#pragma once
#include "miniaudio.h"

namespace Neon
{
class AudioClip
{
public:

private:
   friend class AudioManager;
   ma_decoder decoder = {};
};
}
