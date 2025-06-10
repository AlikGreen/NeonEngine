#pragma once
#include "core/event.h"

namespace Neon
{
class MouseMoveEvent final : public Event
{
public:
    MouseMoveEvent(const float x, const float y, const float deltaX, const float deltaY) : x(x), y(y), deltaX(deltaX), deltaY(deltaY) { }

    [[nodiscard]] float getX() const { return x; }
    [[nodiscard]] float getY() const { return y; }
    [[nodiscard]] float getDeltaX() const { return deltaX; }
    [[nodiscard]] float getDeltaY() const { return deltaY; }
private:
    float x, y;
    float deltaX, deltaY;
};
}
