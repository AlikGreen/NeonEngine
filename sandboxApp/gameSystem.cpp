#include "gameSystem.h"

#include <iostream>

#include "neonEngine.h"
#include "core/ecs/ecsSystem.h"
#include "input/events/keyDownEvent.h"
#include "input/events/mouseButtonDownEvent.h"
#include "input/events/textInputEvent.h"

void GameSystem::startup()
{
    auto* ecsSystem = Neon::Engine::getInstance()->getSystem<Neon::ECSSystem>();
    Neon::Entity entity = 2;
    ecsSystem->getWorld()->addComponent<Transform>(entity);
}

void GameSystem::update()
{
    auto* ecsSystem = Neon::Engine::getInstance()->getSystem<Neon::ECSSystem>();
    auto components = ecsSystem->getWorld()->getComponents<Transform>();

    for (auto[transform] : components)
    {
        transform->x += 1.0f/144.0f;
    }

    frameCount++;
    auto end = std::chrono::high_resolution_clock::now();
    if (std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() > 1000)
    {
        std::cout << frameCount << std::endl;
        start = std::chrono::high_resolution_clock::now();
        frameCount = 0;
    }
}

void GameSystem::event(Neon::Event *event)
{
    if(const auto keyDownEvent = dynamic_cast<Neon::KeyDownEvent*>(event))
    {
        std::cout << std::to_string(static_cast<uint32_t>(keyDownEvent->getKeycode())) << std::endl;
    }
    else if(const auto mouseDownEvent = dynamic_cast<Neon::MouseButtonDownEvent*>(event))
    {
        std::cout << std::to_string(static_cast<uint32_t>(mouseDownEvent->getButton())) << std::endl;
    }

    if(const auto textInputEvent = dynamic_cast<Neon::TextInputEvent*>(event))
    {
        std::cout << textInputEvent->getText() << std::endl;
    }
}
