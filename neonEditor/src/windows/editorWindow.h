#pragma once
#include "core/event.h"

namespace Neon
{
class EditorWindow
{
public:
    virtual ~EditorWindow() = default;

    virtual void startup() {};
    virtual void update()  {};
    virtual void render()  {};
    virtual void event(Event* event) {};
};
}
