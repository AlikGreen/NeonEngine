#include <complex>

#include "AudioManager.h"
#include <filesystem>
#include <ranges>

#include "miniaudio.h"
#include "debug/assert.h"
#include "debug/logger.h"

namespace Neon
{
    AudioManager::AudioManager()
    {
        audioThread = std::thread(&AudioManager::audioThreadLoop, this);
    }

    SoundHandle AudioManager::playSound(AudioClip* clip, SoundHandle soundHandle)
    {
        std::lock_guard lock(commandQueueMutex);
        commandQueue.push({ AudioCommand::Play, clip, soundHandle });

        std::lock_guard audioClipLock(audioClipMutex);
        audioClipsMap.emplace(soundHandle, clip);
        return soundHandle;
    }

    void AudioManager::stopSound(const SoundHandle soundHandle)
    {
        std::lock_guard lock(commandQueueMutex);
        commandQueue.push({ AudioCommand::Stop, nullptr, soundHandle });
    }

    void AudioManager::audioThreadLoop()
    {
        running = true;

        ma_device_config deviceConfig;
        deviceConfig = ma_device_config_init(ma_device_type_playback);
        deviceConfig.playback.format   = ma_format_f32;
        deviceConfig.playback.channels = 2;
        deviceConfig.sampleRate        = 48000;
        deviceConfig.dataCallback      = audioDataCallback;
        deviceConfig.pUserData         = this;

        ma_device device;
        ma_result result = ma_device_init(nullptr, &deviceConfig, &device);
        Assert::check(result == MA_SUCCESS, "Failed to initialize device");

        // --- Waveform generation setup ---
        // ma_waveform_config waveformConfig;
        // waveformConfig = ma_waveform_config_init(device.playback.format, device.playback.channels, device.sampleRate, ma_waveform_type_sine, 0.01, 440.0); // A4 note
        // ma_waveform_init(&waveformConfig, &waveform);

        result = ma_device_start(&device);
        Assert::check(result == MA_SUCCESS, "Failed to start playback device");

        while (running)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }

    void AudioManager::audioDataCallback(ma_device *pDevice, void *pOutput, const void *pInput, ma_uint32 frameCount)
    {
        auto* self = static_cast<AudioManager*>(pDevice->pUserData);
        self->mixClips(static_cast<float *>(pOutput), frameCount);
        // ma_waveform_read_pcm_frames(&waveform, pOutput, frameCount, nullptr);
        (void)pInput; // Unused
    }

    void AudioManager::mixClips(float* pOutF32, ma_uint32 frameCount)
    {
        // zero out buffer
        std::fill_n(pOutF32, frameCount * 2, 0.0f);

        std::lock_guard vlock(audioClipMutex);
        for (const auto& clip : std::ranges::views::values(audioClipsMap))
        {
            //ma_decoder_read_pcm_frames(&clip->decoder, pOutF32, frameCount, nullptr);
        }
    }
}
