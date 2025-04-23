#pragma once
#include <chrono>

#include "core/system.h"
#include "core/ecs/component.h"

struct Transform : public Neon::Component
{
    double x{};
};

class GameSystem final : public Neon::System
{
public:
    void startup() override;
    void update() override;
    void event(Neon::Event *event) override;

private:
    int frameCount = 0;
    std::chrono::time_point<std::chrono::high_resolution_clock> start;
};
