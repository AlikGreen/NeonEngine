#pragma once
#include "core/system.h"

namespace Neon
{
class ScriptingSystem final : public System
{
public:
    void startup() override;
};
}
