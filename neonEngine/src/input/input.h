#pragma once
#include "keyCodes.h"
#include <glm/glm.hpp>

namespace Neon
{
    struct KeyState
    {
        bool pressed;
        bool released;
        bool held;
    };

class Input
{
public:
    static bool isKeyHeld(KeyCode key);
    static bool isKeyReleased(KeyCode key);
    static bool isKeyPressed(KeyCode key);

    static glm::vec2 getMousePosition();
    static glm::vec2 getMouseDelta();

    static void setCursorLocked(bool locked);
    static void setCursorVisible(bool visible);
private:
    friend class InputSystem;
    static std::unordered_map<KeyCode, KeyState> keyStates;
    static glm::vec2 mousePosition;
    static glm::vec2 mouseDelta;
};
}
