#include "world.h"

#include <tiny_gltf.h>

#include "components/tagComponent.h"
#include "components/transformComponent.h"

namespace Neon
{
    Entity World::createEntity() const
    {
        Entity ent = ecs.entity();
        ent.addComponent<Transform>();
        ent.addComponent<Tag>("Entity");
        return ent;
    }

    Entity World::createEmptyEntity() const
    {
        return  ecs.entity();
    }
}
