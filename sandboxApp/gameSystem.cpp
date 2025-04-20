#include "gameSystem.h"

#include <iostream>

#include "input/events/keyDownEvent.h"
#include "input/events/mouseButtonDownEvent.h"
#include "input/events/textInputEvent.h"

void GameSystem::update()
{

}

void GameSystem::event(Neon::Event *event)
{
    if(auto keyDownEvent = dynamic_cast<Neon::KeyDownEvent*>(event))
    {
        std::cout << std::to_string(static_cast<uint32_t>(keyDownEvent->getKeycode())) << std::endl;
    }else if(auto mouseDownEvent = dynamic_cast<Neon::MouseButtonDownEvent*>(event))
    {
        std::cout << std::to_string(static_cast<uint32_t>(mouseDownEvent->getButton())) << std::endl;
    }

    if(auto textInputEvent = dynamic_cast<Neon::TextInputEvent*>(event))
    {
        std::cout << textInputEvent->getText() << std::endl;
    }
}
