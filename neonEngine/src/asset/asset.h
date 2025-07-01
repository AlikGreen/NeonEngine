#pragma once

namespace Neon
{
    class Asset
    {
    public:
        virtual ~Asset() = default;
    };

    template <class T>
    concept DerivesAsset = std::is_base_of_v<Asset, T>;
}
