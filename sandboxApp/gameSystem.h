#pragma once
#include <chrono>

#include "core/system.h"

class GameSystem final : public Neon::System
{
public:
    void postStartup() override;
    void update() override;
    void event(Neon::Event *event) override;

private:
    int frameCount = 0;
    std::chrono::time_point<std::chrono::high_resolution_clock> start;
};
