#include "world.h"

#include <tiny_gltf.h>

#include "components/tagComponent.h"
#include "components/transformComponent.h"

namespace Neon
{
    Entity World::createEntity()
    {
        Entity ent = ecs.entity();
        ent.addComponent<Transform>();
        ent.addComponent<Tag>("Entity");
        return ent;
    }

    Entity World::createEmptyEntity()
    {
        return  ecs.entity();
    }
}
