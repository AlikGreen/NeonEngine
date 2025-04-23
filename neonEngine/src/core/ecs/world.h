#pragma once
#include <typeindex>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "component.h"
#include "componentList.h"
#include "Entity.h"

namespace Neon
{

struct TypeSetHasher {
    size_t operator()(std::unordered_set<std::type_index> const& s) const noexcept {
        size_t seed = 0;
        for (auto const& ti : s) {
            // XOR‐combine each element’s hash_code:
            seed ^= ti.hash_code()
                  + 0x9e3779b97f4a7c15ULL
                  + (seed << 6)
                  + (seed >> 2);
        }
        return seed;
    }
};

using TypeSet = std::unordered_set<std::type_index>;

class World
{
public:
    template<DerivesComponent T, typename... Args>
    bool addComponent(const Entity entity, Args&&... args)
    {
        T* component = new T(std::forward<Args>(args)...);
        auto typeIndex = std::type_index(typeid(T));

        if(entityComponentTypes[entity].contains(typeIndex)) return false;
        entityComponentTypes[entity].insert(typeIndex);
        components.push_back(component);

        entityComponentMap[entity].push_back(component);

        if(typeComponentMap[{typeIndex}] == nullptr)
        {
            typeComponentMap[{typeIndex}] = new ComponentList<T>();
        }

        ComponentList<T>* componentList = dynamic_cast<ComponentList<T>*>(typeComponentMap[{typeIndex}]);
        componentList->push_back(component);

        return true;
    }

    template<typename... Types>
    ComponentList<Types...>& getComponents()
    {
        const auto key = std::unordered_set<std::type_index>{ std::type_index(typeid(Types))... };
        const auto it = typeComponentMap.find(key);
        if (it == typeComponentMap.end())
            throw std::runtime_error("Component list not found for the given types");

        return *static_cast<ComponentList<Types...>*>(it->second);
    }
private:
    std::vector<Component*> components{};
    std::unordered_map<Entity, std::vector<Component*>> entityComponentMap{};
    std::unordered_map<Entity, std::unordered_set<std::type_index>> entityComponentTypes{};
    std::unordered_map<TypeSet, ComponentListBase*, TypeSetHasher> typeComponentMap{};
};
}
