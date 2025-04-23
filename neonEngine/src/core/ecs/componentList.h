#pragma once
#include <stdexcept>
#include <vector>

#include "component.h"

namespace Neon
{
    class ComponentListBase
    {
    public:
        virtual ~ComponentListBase() = default;
    };

    template <typename... Types>
    class ComponentList final : public ComponentListBase
    {
    public:
        [[nodiscard]] size_t size() const
        {
            if constexpr (sizeof...(Types) == 0)
            {
                return 0;
            } else
            {
                return check_sizes_impl(std::index_sequence_for<Types...>{});
            }
        }

        template<typename... ResultTypes>
        std::tuple<ResultTypes*...> at(size_t index)
        {
            static_assert(sizeof...(ResultTypes) == sizeof...(Types),
                         "Number of template parameters must match number of vectors");

            if (index >= size())
            {
                throw std::out_of_range("Index out of range");
            }

            return get_tuple_at_impl<ResultTypes...>(index, std::index_sequence_for<ResultTypes...>{});
        }

        template<typename... ResultTypes, size_t... Indices>
        std::tuple<ResultTypes*...> get_tuple_at_impl(size_t index, std::index_sequence<Indices...>)
        {
            return std::tie(std::get<Indices>(components)[index]...);
        }

        template<typename... Args>
        void push_back(Args*... args)
        {
            static_assert(sizeof...(Args) == sizeof...(Types),
                         "Number of arguments must match number of vectors");

            (std::get<std::vector<Types*>>(components).push_back(args), ...);
            current_size++;
        }
    private:
        std::tuple<std::vector<Types*>...> components;
        size_t current_size = 0;

        template<size_t... Indices>
        size_t check_sizes_impl(std::index_sequence<Indices...>) const
        {
            size_t sizes[] = {std::get<Indices>(components).size()...};
            for (size_t i = 1; i < sizeof...(Types); ++i)
            {
                if (sizes[i] != sizes[0])
                {
                    throw std::logic_error("Inconsistent vector sizes in ParallelArray");
                }
            }
            return sizes[0];
        }

        template<typename Func, size_t... Indices>
        void for_each_vector_impl(Func&& func, std::index_sequence<Indices...>)
        {
            (func(std::get<Indices>(components)), ...);
        }
    public:
        class Iterator
        {
        public:
            // Iterator traits
            using iterator_category = std::random_access_iterator_tag;
            using value_type = std::tuple<Types*...>;
            using difference_type = std::ptrdiff_t;
            using pointer = void;  // Not providing arrow operator
            using reference = value_type;

            Iterator(ComponentList& componentList, size_t position) : componentList(componentList), position(position) { }

            template<size_t... Indices>
            reference dereference_impl(std::index_sequence<Indices...>) const
            {
                return std::tie(std::get<Indices>(componentList.components)[position]...);
            }

            reference operator*() const
            {
                return dereference_impl(std::index_sequence_for<Types...>{});
            }

            Iterator& operator++()
            {
                ++position;
                return *this;
            }

            Iterator operator++(int)
            {
                Iterator temp = *this;
                ++position;
                return temp;
            }

            Iterator& operator--()
            {
                --position;
                return *this;
            }

            Iterator operator--(int)
            {
                Iterator temp = *this;
                --position;
                return temp;
            }

            Iterator operator+(const difference_type n) const
            {
                return Iterator(componentList, position + n);
            }

            Iterator operator-(const difference_type n) const
            {
                return Iterator(componentList, position - n);
            }

            difference_type operator-(const Iterator& other) const
            {
                return position - other.position;
            }

            Iterator& operator+=(const difference_type n)
            {
                position += n;
                return *this;
            }

            Iterator& operator-=(const difference_type n)
            {
                position -= n;
                return *this;
            }

            reference operator[](difference_type n) const
            {
                return *(*this + n);
            }

            bool operator==(const Iterator& other) const
            {
                return &componentList == &other.componentList && position == other.position;
            }

            bool operator!=(const Iterator& other) const
            {
                return !(*this == other);
            }

            bool operator<(const Iterator& other) const
            {
                return position < other.position;
            }

            bool operator>(const Iterator& other) const
            {
                return position > other.position;
            }

            bool operator<=(const Iterator& other) const
            {
                return position <= other.position;
            }

            bool operator>=(const Iterator& other) const
            {
                return position >= other.position;
            }
        private:
            ComponentList& componentList;
            size_t position;
        };

        Iterator begin()
        {
            return Iterator(*this, 0);
        }

        Iterator end()
        {
            return Iterator(*this, size());
        }
    };
}
