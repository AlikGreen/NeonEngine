#include "soundHandle.h"

#include <random>

namespace Neon
{
    SoundHandle::SoundHandle()
    {
        handle = generateRandomHandle();
    }

    SoundHandle::operator unsigned long long() const
    {
        return handle;
    }

    bool SoundHandle::operator==(const SoundHandle &) const
    {
        return handle == this->handle;
    }

    bool SoundHandle::operator!=(const SoundHandle &) const
    {
        return handle != this->handle;
    }

    // TODO maybe make a random class
    uint64_t SoundHandle::generateRandomHandle()
    {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_int_distribution<uint64_t> distrib(1, std::numeric_limits<uint64_t>::max());
        return distrib(gen);
    }
}
