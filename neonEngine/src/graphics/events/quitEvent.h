#pragma once
#include "core/event.h"

namespace Neon
{
class QuitEvent : public Event
{
public:
    QuitEvent() = default;
};
}
