#pragma once
#include <chrono>

#include "core/system.h"

class GameSystem final : public Neon::System
{
public:
    void startup() override;
    void update() override;
    void event(Neon::Event *event) override;
private:
    bool focused = false;
};
