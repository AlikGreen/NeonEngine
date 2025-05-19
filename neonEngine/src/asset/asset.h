#pragma once
#include <string>

#include "streams/assetStream.h"


namespace Neon
{
    class Asset
    {
    public:
        virtual ~Asset() = default;

        virtual void load(const std::string& filePath) = 0;

        virtual void serialize(AssetStream& stream) = 0;
        virtual void deserialize(AssetStream& stream) = 0;
    };

    template <class T>
    concept DerivesAsset = std::is_base_of_v<Asset, T>;
}
