#pragma once
#include "system.h"

namespace Neon
{
class CoreSystem final : public System
{
public:
    void event(Event* event) override;
};
}
