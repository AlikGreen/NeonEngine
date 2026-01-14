#include "scene.h"

#include "components/parentComponent.h"
#include "components/tagComponent.h"
#include "components/transformComponent.h"

namespace Neon
{

    ECS::Registry& Scene::getRegistry()
    {
        return registry;
    }

    ECS::Entity Scene::createEntity(const std::string& name)
    {
        ECS::Entity entity = registry.createEntity();

        entity.emplace<Transform>();
        entity.emplace<Tag>(name);
        entity.emplace<Parent>();

        return entity;
    }

    ECS::Entity Scene::import(Scene& scene)
    {
        const std::vector<ECS::Entity> newEntities = registry.merge(scene.getRegistry());

        const ECS::Entity parent = createEntity(scene.name);

        for(auto entity : newEntities)
        {
            if(!entity.has<Parent>())
                continue;

            auto& p = entity.get<Parent>();

            if(!p.hasParent())
            {
                p.setParent(parent);
            }
        }

        return parent;
    }
}
