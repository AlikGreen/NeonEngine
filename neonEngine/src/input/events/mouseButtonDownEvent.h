#pragma once

namespace Neon
{
    class MouseButtonDownEvent final : public Event
    {
    public:
        explicit MouseButtonDownEvent(const MouseButton keycode) : button(keycode) { };

        [[nodiscard]] MouseButton getButton() const { return button; }
    private:
        MouseButton button;
    };
}
