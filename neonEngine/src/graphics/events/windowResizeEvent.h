#pragma once
#include <cstdint>

#include "core/event.h"

namespace Neon
{
class WindowResizeEvent final : public Event
{
    public:
    WindowResizeEvent(const int32_t width, const int32_t height) : width(width), height(height) {}

    [[nodiscard]] int32_t getWidth() const { return width; }
    [[nodiscard]] int32_t getHeight() const { return height; }
private:
    int width, height;
};
}
