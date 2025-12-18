#pragma once
#include <neonRHI/neonRHI.h>
#include "core/event.h"

namespace Neon
{
    class RhiWindowEvent final : public Event
    {
    public:
        explicit RhiWindowEvent(const RHI::Event &event) : event(event) {  }
        RHI::Event event;
    };
}
