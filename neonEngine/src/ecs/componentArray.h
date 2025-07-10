#pragma once
#include "entityID.h"

namespace Neon
{
class IComponentArray
{
public:
    virtual ~IComponentArray() = default;
    virtual void entityDestroyed(EntityID entity) = 0;
    [[nodiscard]] virtual std::unique_ptr<IComponentArray> clone() const = 0;
    virtual void copyTo(IComponentArray* other, const std::unordered_map<EntityID, EntityID>& entityMap) const = 0;
    [[nodiscard]] virtual std::vector<EntityID> getAllEntities() const = 0;
    [[nodiscard]] virtual std::unique_ptr<IComponentArray> createEmpty() const = 0;
};

template<typename T>
class ComponentArray final : public IComponentArray
{
public:
    void insertData(const EntityID entity, T component)
    {
        if (entityToIndex.contains(entity))
        {
            size_t index = entityToIndex[entity];
            components[index] = component;
            return;
        }

        const size_t newIndex = size;
        entityToIndex[entity] = newIndex;
        indexToEntity[newIndex] = entity;

        components.push_back(component);
        ++size;
    }

    void removeData(const EntityID entity)
    {
        if (!entityToIndex.contains(entity)) return;

        size_t indexOfRemovedEntity = entityToIndex[entity];
        size_t indexOfLastElement = size - 1;

        components[indexOfRemovedEntity] = components[indexOfLastElement];

        const EntityID entityOfLastElement = indexToEntity[indexOfLastElement];
        entityToIndex[entityOfLastElement] = indexOfRemovedEntity;
        indexToEntity[indexOfRemovedEntity] = entityOfLastElement;

        entityToIndex.erase(entity);
        indexToEntity.erase(indexOfLastElement);

        --size;
    }

    T& getData(const EntityID entity)
    {
        return components[entityToIndex[entity]];
    }

    bool hasData(const EntityID entity) const
    {
        return entityToIndex.contains(entity);
    }

    void entityDestroyed(const EntityID entity) override
    {
        if (hasData(entity))
        {
            removeData(entity);
        }
    }

    std::unique_ptr<IComponentArray> clone() const override
    {
        auto cloned = std::make_unique<ComponentArray>();
        cloned->components = components;
        cloned->entityToIndex = entityToIndex;
        cloned->indexToEntity = indexToEntity;
        cloned->size = size;
        return cloned;
    }

    void copyTo(IComponentArray* other, const std::unordered_map<EntityID, EntityID>& entityMap) const override
    {
        auto* typedOther = static_cast<ComponentArray*>(other);

        for (const auto& [oldEntity, index] : entityToIndex)
        {
            auto it = entityMap.find(oldEntity);
            if (it != entityMap.end())
            {
                EntityID newEntity = it->second;
                typedOther->insertData(newEntity, components[index]);
            }
        }
    }

    std::unique_ptr<IComponentArray> createEmpty() const override
    {
        return std::make_unique<ComponentArray>();
    }

    std::vector<EntityID> getAllEntities() const override
    {
        std::vector<EntityID> entities;
        entities.reserve(size);
        for (const auto& [entity, index] : entityToIndex)
        {
            entities.push_back(entity);
        }
        return entities;
    }

    // Iterator support for systems
    T* begin() { return components.data(); }
    T* end() { return components.data() + size; }
    const T* begin() const { return components.data(); }
    const T* end() const { return components.data() + size; }

    size_t getSize() const { return size; }
    EntityID getEntity(const size_t index) const
    {
        return indexToEntity.at(index);
    }
private:
    std::vector<T> components;
    std::unordered_map<EntityID, size_t> entityToIndex;
    std::unordered_map<size_t, EntityID> indexToEntity;
    size_t size = 0;
};
}
