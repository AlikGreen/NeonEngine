#pragma once
#include "audioClip.h"
#include "soundHandle.h"

namespace Neon
{
struct AudioCommand
{
    enum Type { Play, Stop } type;
    Ref<AudioClip> clip;
    SoundHandle handle;
};
}
