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
    float speed = 1.0f;
    float volume = 1.0f;
    float pitch = 1.0f;
    bool loop = true;
};
}
