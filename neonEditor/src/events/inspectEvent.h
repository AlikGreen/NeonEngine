#pragma once
#include <any>

#include "core/event.h"

namespace Neon
{
class InspectEvent final : public Event
{
public:
    explicit InspectEvent(const std::variant<ECS::Entity, AssetID> &inspected)
        : inspected(inspected)
    {  }

    std::variant<ECS::Entity, AssetID> inspected;
};
}
