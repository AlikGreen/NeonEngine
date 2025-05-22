#pragma once
#include <limits>
#include <random>

namespace Neon
{
    class AssetHandle
    {
    public:
        AssetHandle() : handle(generateRandomHandle()) {}
        AssetHandle(const AssetHandle& other) : handle(other.handle) {}

        bool operator==(const AssetHandle& other) const
        {
            return handle == other.handle;
        }

        bool operator!=(const AssetHandle& other) const
        {
            return !(*this == other);
        }

        explicit operator uint64_t() const
        {
            return handle;
        }
    private:
        uint64_t handle;

        // Static member to generate a random size_t
        static uint64_t generateRandomHandle()
        {
            static std::random_device rd;
            static std::mt19937 gen(rd());
            static std::uniform_int_distribution<uint64_t> distrib(1, std::numeric_limits<uint64_t>::max());
            return distrib(gen);
        }
    };
}

namespace std
{
    template<>
    struct hash<Neon::AssetHandle>
    {
        std::size_t operator()(const Neon::AssetHandle& handle) const noexcept
        {
            return static_cast<std::size_t>(handle);
        }
    };
}