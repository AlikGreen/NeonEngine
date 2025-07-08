#pragma once
#include "asset/asset.h"

namespace Neon
{
class Texture : public Asset
{
public:
    ~Texture() override = default;

    virtual uint32_t getWidth() = 0;
    virtual uint32_t getHeight() = 0;
    virtual uint32_t getDepth() = 0;
};
}
