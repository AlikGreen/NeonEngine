#pragma once

namespace Neon
{
class SoundHandle
{
public:
    SoundHandle();

    explicit operator uint64_t() const;

    bool operator==(const SoundHandle &) const;
    bool operator!=(const SoundHandle &) const;
private:
    uint64_t handle;

    static uint64_t generateRandomHandle();
};
}

template<>
struct std::hash<Neon::SoundHandle>
{
    uint64_t operator()(const Neon::SoundHandle& handle) const noexcept
    {
        return static_cast<uint64_t>(handle);
    }
};
