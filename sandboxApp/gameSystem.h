#pragma once
#include "core/system.h"


class GameSystem final : public Neon::System
{
public:
    void update() override;
    void event(Neon::Event *event) override;
};
