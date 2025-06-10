#pragma once
#include <queue>
#include <thread>

#include "audioClip.h"
#include "audioCommand.h"
#include "miniaudio.h"
#include "soundHandle.h"

namespace Neon
{
class AudioManager
{
public:
    AudioManager();
    SoundHandle playSound(AudioClip* clip, SoundHandle soundHandle = SoundHandle());
    void stopSound(SoundHandle soundHandle);
private:
    std::thread audioThread;
    std::atomic_bool running;

    std::queue<AudioCommand> commandQueue;
    std::mutex commandQueueMutex;

    std::unordered_map<SoundHandle, Ref<AudioClip>> audioClipsMap;
    std::mutex audioClipMutex;

    void audioThreadLoop();
    void mixClips(float* pOutF32, ma_uint32 frameCount);
    static void audioDataCallback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount);
};
}
