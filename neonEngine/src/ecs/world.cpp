#include "world.h"

#include <tiny_gltf.h>

#include "components/parentComponent.h"
#include "components/tagComponent.h"
#include "components/transformComponent.h"

namespace Neon
{
    std::unordered_map<uint32_t, World*> World::worlds = std::unordered_map<uint32_t, World*>();
    uint32_t World::nextWorldId = 0;

    bool Entity::hasParent()
    {
        return getComponent<Parent>().hasParent();
    }

    Entity Entity::getParent()
    {
        return getComponent<Parent>().getParent();
    }

    void Entity::setParent(const Entity parent)
    {
        getComponent<Parent>().setParent(parent);
    }

    void Entity::destroy() const
    {
        getWorld()->destroyEntity(*this);
    }

    World * Entity::getWorld(const uint32_t id)
    {
        return World::getWorld(id);
    }

    World::World()
    {
        index = nextWorldId;
        worlds.emplace(nextWorldId++, this);
    }

    World * World::getWorld(const uint32_t id)
    {
        return worlds.at(id);
    }

    Entity World::createEntity()
    {
        Entity entity = entityManager.createEntity(index);
        entity.addComponent<Transform>();
        entity.addComponent<Tag>("Entity");
        entity.addComponent<Parent>();
        return entity;
    }

    void World::destroyEntity(const EntityID entity)
    {
        componentManager.entityDestroyed(entity);
        entityManager.destroyEntity(entity);
    }

    void World::merge(const World &other)
    {
        auto otherEntities = other.componentManager.getAllEntitiesWithComponents();

        std::unordered_map<EntityID, EntityID> entityMap;

        for (EntityID otherEntity : otherEntities)
        {
            const EntityID newEntity = createEntity();
            entityMap[otherEntity] = newEntity;
        }

        other.componentManager.copyTo(componentManager, entityMap);

        for (const auto &newEntity: entityMap | std::views::values)
        {
            if (componentManager.hasComponent<Parent>(newEntity))
            {
                auto& parentComponent = componentManager.getComponent<Parent>(newEntity);
                if (parentComponent.hasParent())
                {
                    EntityID oldParentId = parentComponent.getParent();

                    auto parentMapIt = entityMap.find(oldParentId);
                    if (parentMapIt != entityMap.end())
                    {
                        parentComponent.setParent(parentMapIt->second);
                    }
                    else
                    {
                        parentComponent.setParent(EntityID::None);
                    }
                }
            }
        }
    }

    uint32_t World::getLivingEntityCount() const
    {
        return entityManager.getLivingEntityCount();
    }

    std::vector<EntityID> World::getEntities() const
    {
        return componentManager.getAllEntitiesWithComponents();;
    }
}
