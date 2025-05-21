#include <complex>

#include "AudioManager.h"
#include <filesystem>

#include "miniaudio.h"

namespace Neon
{
void AudioManager::playSound(std::string filePath)
    {
        ma_result result;
        ma_engine engine;

        result = ma_engine_init(NULL, &engine);
        if (result != MA_SUCCESS) {
            std::cerr << "Failed to initialize audio engine." << std::endl;
            return;
        }

        if (!std::filesystem::exists(filePath)) {
            std::cerr << "File not found: " << filePath << std::endl;
            return;
        }

        ma_engine_play_sound(&engine, filePath.c_str(), NULL);

        printf("Press Enter to quit...");
        getchar();

        ma_engine_uninit(&engine);
    }
}