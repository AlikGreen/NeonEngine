#pragma once

#include <unordered_map>
#include <memory>
#include <ranges>
#include <typeindex>

#include "componentArray.h"


namespace Neon
{
    class ComponentManager
    {
    public:
        template<typename T>
        void addComponent(EntityID entity, T component)
        {
            getComponentArray<T>()->insertData(entity, component);
        }

        template<typename T>
        void removeComponent(EntityID entity)
        {
            getComponentArray<T>()->removeData(entity);
        }

        template<typename T>
        T& getComponent(EntityID entity)
        {
            return getComponentArray<T>()->getData(entity);
        }

        template<typename T>
        bool hasComponent(EntityID entity)
        {
            return getComponentArray<T>()->hasData(entity);
        }

        void entityDestroyed(const EntityID entity) const
        {
            for (const auto &val: componentArrays | std::views::values)
            {
                val->entityDestroyed(entity);
            }
        }

        template<typename T>
        ComponentArray<T>* getArray()
        {
            return getComponentArray<T>().get();
        }

        std::vector<EntityID> getAllEntitiesWithComponents() const
        {
            std::vector<EntityID> allEntities;
            for (const auto& array : componentArrays  | std::views::values)
            {
                auto entities = array->getAllEntities();
                allEntities.insert(allEntities.end(), entities.begin(), entities.end());
            }

            std::ranges::sort(allEntities);
            allEntities.erase(std::ranges::unique(allEntities).begin(), allEntities.end());

            return allEntities;
        }

        void copyTo(ComponentManager& other, const std::unordered_map<EntityID, EntityID>& entityMap) const
        {
            for (const auto& [typeIndex, sourceArray] : componentArrays)
            {
                if (!other.componentArrays.contains(typeIndex))
                {
                    // Create empty array instead of cloning
                    other.componentArrays[typeIndex] = sourceArray->createEmpty();
                }
                sourceArray->copyTo(other.componentArrays[typeIndex].get(), entityMap);
            }
        }

        ComponentManager clone() const
        {
            ComponentManager cloned;
            std::unordered_map<EntityID, EntityID> identityMap;

            auto allEntities = getAllEntitiesWithComponents();
            for (EntityID entity : allEntities)
            {
                identityMap[entity] = entity;
            }

            copyTo(cloned, identityMap);
            return cloned;
        }
    private:
        std::unordered_map<std::type_index, std::shared_ptr<IComponentArray>> componentArrays;

        template<typename T>
        std::shared_ptr<ComponentArray<T>> getComponentArray()
        {
            const auto typeName = std::type_index(typeid(T));

            if (!componentArrays.contains(typeName))
            {
                componentArrays[typeName] = std::make_shared<ComponentArray<T>>();
            }

            return std::static_pointer_cast<ComponentArray<T>>(componentArrays[typeName]);
        }
    };
}
