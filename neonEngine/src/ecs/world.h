#pragma once
#include <unordered_map>

#include "componentList.h"
#include "entity.h"
#include "flecs.h"
#include "asset/asset.h"

namespace Neon
{
class World : public Asset
{
public:
    template<typename... Types>
    ComponentList<Types...> getComponents()
    {
        flecs::query<Types...> q = ecs.query<Types...>();
        return ComponentList<Types...>(ecs, std::move(q));
    }

    Entity createEntity() const;
    Entity createEmptyEntity() const;
private:
    flecs::world ecs;
};
}
