#include "input.h"

#include "core/engine.h"
#include "graphics/renderSystem.h"

namespace Neon
{
    std::unordered_map<KeyCode, KeyState> Input::keyStates{};
    glm::vec2 Input::mousePosition{};
    glm::vec2 Input::mouseDelta{};

    bool Input::isKeyHeld(const KeyCode key)
    {
        return keyStates[key].held;
    }

    bool Input::isKeyReleased(const KeyCode key)
    {
        return keyStates[key].released;
    }

    bool Input::isKeyPressed(const KeyCode key)
    {
        return keyStates[key].pressed;
    }

    glm::vec2 Input::getMousePosition()
    {
        return mousePosition;
    }

    glm::vec2 Input::getMouseDelta()
    {
        return mouseDelta;
    }

    void Input::setCursorLocked(const bool locked)
    {
        Engine::getSystem<GraphicsSystem>()->getWindow()->setCursorLocked(locked);
    }

    void Input::setCursorVisible(const bool visible)
    {
        Engine::getSystem<GraphicsSystem>()->getWindow()->setCursorVisible(visible);
    }
}
