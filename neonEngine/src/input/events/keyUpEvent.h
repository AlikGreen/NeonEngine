#pragma once
#include <SDL3/SDL.h>

#include "../../core/event.h"
namespace Neon
{
    class KeyUpEvent final : public Event
    {
    public:
        KeyUpEvent(const KeyCode keycode, const KeyMod modifier) : keycode(keycode), modifier(modifier) { };

        [[nodiscard]] KeyCode getKeycode() const { return keycode; }
        [[nodiscard]] KeyMod getModifier() const { return modifier; }
    private:
        KeyCode keycode;
        KeyMod modifier;
    };
}
