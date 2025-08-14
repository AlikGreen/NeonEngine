#pragma once

namespace Neon
{
class WindowResizeEvent final : public Event
{
public:
    WindowResizeEvent(int width, int height) : width(width), height(height)
    {

    }
    float width, height;
};
}
