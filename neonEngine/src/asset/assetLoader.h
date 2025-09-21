#pragma once
#include "core/prefab.h"

namespace Neon
{
class AssetLoader
{
public:
    virtual ~AssetLoader() = default;

    virtual void* load(const std::string &filepath) = 0;
};
}
