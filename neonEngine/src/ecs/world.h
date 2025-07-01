#pragma once

#include "componentList.h"
#include "componentManager.h"
#include "entityManager.h"

namespace Neon
{
    class World;

    class Entity
    {
    public:
        Entity(const uint32_t id, const uint32_t worldIndex) : id(id), world(worldIndex) {}
        Entity(const EntityID entityId) : id(entityId.getEntityId()), world(entityId.getWorldId()) {}

        [[nodiscard]] uint32_t getId() const { return id; }
        [[nodiscard]] World* getWorld() const { return getWorld(world); }

        [[nodiscard]] bool hasParent();
        [[nodiscard]] Entity getParent();
        void setParent(Entity parent);

        template<typename T, typename... Args>
        T& addComponent(Args... args);

        template<typename T>
        void removeComponent() const;

        template<typename T>
        T& getComponent();

        template<typename T>
        [[nodiscard]] bool hasComponent() const;

        void destroy() const;

        operator EntityID() const { return EntityID(id, world); }
    private:
        static World* getWorld(uint32_t id);

        uint32_t id;
        uint32_t world;
    };

    class World
    {
    public:
        World();

        static World* getWorld(uint32_t id);
        Entity createEntity();
        void destroyEntity(EntityID entity);
        void merge(const World& other);
        uint32_t getLivingEntityCount() const;
        std::vector<EntityID> getEntities() const;

        template<typename T, typename... Args>
        void addComponent(const EntityID entity, Args... args)
        {
            componentManager.addComponent<T>(entity, T(std::forward<Args>(args)...));
        }

        template<typename T>
        void removeComponent(const EntityID entity)
        {
            componentManager.removeComponent<T>(entity);
        }

        template<typename T>
        T& getComponent(const EntityID entity)
        {
            return componentManager.getComponent<T>(entity);
        }

        template<typename T>
        bool hasComponent(const EntityID entity)
        {
            return componentManager.hasComponent<T>(entity);
        }


        template<typename... Types>
        ComponentList<Types...> getComponents()
        {
            return ComponentList<Types...>(componentManager.getArray<Types>()...);
        }
    private:
        friend class EcsSystem;

        EntityManager entityManager;
        ComponentManager componentManager;
        uint32_t index;

        static uint32_t nextWorldId;
        static std::unordered_map<uint32_t, World*> worlds;
    };

    template<typename T, typename... Args>
    T& Entity::addComponent(Args... args)
    {
        getWorld()->addComponent<T>(*this, std::forward<Args>(args)...);
        return getComponent<T>();
    }

    template<typename T>
    void Entity::removeComponent() const
    {
        getWorld()->removeComponent<T>(*this);
    }

    template<typename T>
    T & Entity::getComponent()
    {
        return getWorld()->getComponent<T>(*this);
    }

    template<typename T>
    bool Entity::hasComponent() const
    {
        return getWorld()->hasComponent<T>(*this);
    }
}
