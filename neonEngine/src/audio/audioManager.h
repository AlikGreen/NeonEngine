#pragma once

namespace Neon
{
class AudioManager
{
public:
    static void initialize();
    static void playSound(std::string filePath);
    static void shutdown();
};
}
