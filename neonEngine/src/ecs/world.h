#pragma once
#include <unordered_map>

#include "componentList.h"
#include "entity.h"
#include "flecs.h"

namespace Neon
{
class World
{
public:
    template<typename... Types>
    ComponentList<Types...> getComponents()
    {
        // ecs.query<>() is a const method on flecs::world, so this is fine.
        flecs::query<Types...> q = ecs.query<Types...>();
        // 'ecs' is the flecs::world member of Neon::World.
        // It's passed as a non-const reference to ComponentList.
        return ComponentList<Types...>(ecs, std::move(q));
    }

    Entity createEntity();
    Entity createEmptyEntity();
private:
    flecs::world ecs;
};
}
