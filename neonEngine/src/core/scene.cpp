#include "scene.h"

#include "prefab.h"
#include "components/parentComponent.h"
#include "components/tagComponent.h"
#include "components/transformComponent.h"

namespace Neon
{

    ECS::Registry & Scene::getRegistry()
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

    void Scene::import(Prefab* entity)
    {
        registry.merge(entity->scene.getRegistry());
    }
}
