#pragma once
#include <SDL3/SDL.h>

#include "input/keyCodes.h"


namespace Neon
{
class KeyDownEvent final : public Event
{
public:
    KeyDownEvent(const KeyCode keycode, const KeyMod modifier) : keycode(keycode), modifier(modifier) { };

    [[nodiscard]] KeyCode getKeycode() const { return keycode; }
    [[nodiscard]] KeyMod getModifier() const { return modifier; }
private:
    KeyCode keycode;
    KeyMod modifier;
};
}
