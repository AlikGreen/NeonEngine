#pragma once
#include "assetStream.h"

namespace Neon
{
class AssetDeserializer
{
public:
    virtual ~AssetDeserializer() = default;

    virtual void* deserialize(AssetStream* assetStream) = 0;
};
}
