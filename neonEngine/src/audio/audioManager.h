#pragma once
#include "audioClip.h"
#include "sound.h"

namespace Neon
{
struct SoundSettings
{

};

class AudioManager
{
public:
    AudioManager();
    Sound createSound(const AudioClip &clip);
    void shutdown();
private:
    ma_engine m_engine;
};
}
