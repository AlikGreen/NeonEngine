#pragma once

#include <tuple>
#include <cassert>

#include "componentArray.h"

namespace Neon
{
    template<typename... Types>
    class ComponentList
    {
    public:
        explicit ComponentList(ComponentArray<Types>*... componentArrays) : arrays(componentArrays...)
        {
            maxSize = std::min({componentArrays->getSize()...});
        }

        size_t size() const
        {
            size_t count = 0;
            if (maxSize == 0) return 0;
            if(cachedSize != 0xffffffff) return cachedSize;

            for (size_t i = 0; i < maxSize; ++i)
            {
                EntityID entity = std::get<0>(arrays)->getEntity(i);
                if (entityHasAllComponents(entity))
                {
                    ++count;
                }
            }
            cachedSize = count;
            return count;
        }

        std::tuple<EntityID, Types&...> operator[](const size_t index) const
        {
            size_t count = 0;
            for (size_t i = 0; i < maxSize; ++i)
            {
                EntityID entity = std::get<0>(arrays)->getEntity(i);
                if (entityHasAllComponents(entity))
                {
                    if (count == index)
                    {
                        return std::tie(entity, std::get<ComponentArray<Types>*>(arrays)->getData(entity)...);
                    }
                    ++count;
                }
            }
            return operator[](0);
        }

        class Iterator
        {
        public:
            Iterator(ComponentList* l, size_t i) : list(l), index(i)
            {
                findNext();
            }

            std::tuple<EntityID, Types&...> operator*()
            {
                EntityID entity = std::get<0>(list->arrays)->getEntity(index);
                return std::tie(entity, std::get<ComponentArray<Types>*>(list->arrays)->getData(entity)...);
            }

            Iterator& operator++()
            {
                ++index;
                findNext();
                return *this;
            }

            bool operator!=(const Iterator& other) const
            {
                return index != other.index;
            }
        private:
            ComponentList* list;
            size_t index;

            void findNext()
            {
                while (index < list->maxSize)
                {
                    EntityID entity = std::get<0>(list->arrays)->getEntity(index);
                    if (list->entityHasAllComponents(entity))
                    {
                        break;
                    }
                    ++index;
                }
            }
        };

        Iterator begin()
        {
            return Iterator(this, 0);
        }

        Iterator end()
        {
            return Iterator(this, maxSize);
        }
    private:
        std::tuple<ComponentArray<Types>*...> arrays;
        size_t currentIndex = 0;
        size_t maxSize = 0;

        mutable size_t cachedSize = 0xffffffff;

        template<typename T>
        static bool entityHasComponent(EntityID entity, ComponentArray<T>* arr)
        {
            return arr->hasData(entity);
        }

        bool entityHasAllComponents(EntityID entity) const
        {
            return std::apply([entity, this](auto*... arrays)
            {
                return (entityHasComponent(entity, arrays) && ...);
            }, arrays);
        }
    };
}
