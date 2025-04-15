#pragma once
#include "event.h"

namespace Neon
{
    class System
    {
    public:
        virtual ~System() = default;

        virtual void startup() { }
        virtual void shutdown() { }

        virtual void preRender() { }
        virtual void postRender() { }
        virtual void render() { }

        virtual void preUpdate() { }
        virtual void postUpdate() { }
        virtual void update() { }

        virtual void event(Event* event) { }
    };
}
