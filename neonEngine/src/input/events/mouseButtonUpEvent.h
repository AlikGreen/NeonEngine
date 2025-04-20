#pragma once
#include <SDL3/SDL.h>

#include "../../core/event.h"

namespace Neon
{
    class MouseButtonUpEvent final : public Event
    {
    public:
        explicit MouseButtonUpEvent(const MouseButton keycode) : button(keycode) { };

        [[nodiscard]] MouseButton getButton() const { return button; }
    private:
        MouseButton button;
    };
}
