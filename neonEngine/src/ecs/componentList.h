#pragma once

#include <tuple>
#include <cassert>
#include <flecs.h>

namespace Neon
{
    template<typename... Components>
    class ComponentList
    {
        flecs::world&                 world;
        flecs::query<Components...>   query;

    public:
        ComponentList(flecs::world& world, flecs::query<Components...> q)
            : world(world)
            , query(std::move(q))
        { }

        class Iterator
        {
            ecs_iter_t  iterData;
            flecs::iter iter;
            bool        alive;
            std::size_t row;

            template<std::size_t... Is>
            auto get_components_tuple(std::index_sequence<Is...>) const
            {
                return std::tuple<Components&...>
                {
                    (iter.field_at<Components>(Is, row))...
                };
            }

            void find_next_valid_batch()
            {
                while (iter.next())
                {
                    if (iter.count() > 0)
                    {
                        alive = true;
                        row = 0;
                        return;
                    }
                }
                alive = false;
            }

        public:
            Iterator(flecs::world& world_ref, const flecs::query<Components...>& query_ref)
              : iterData( ecs_query_iter(world_ref.c_ptr(), query_ref.c_ptr()))
              , iter(&iterData)
              , alive(false)
              , row(0)
            {
                find_next_valid_batch();
            }

            Iterator()
              : iterData{}, iter{nullptr}, alive(false), row(0)
            { }

            bool operator!=(const Iterator& other) const
            {
                return alive != other.alive;
            }

            Iterator& operator++()
            {
                assert(alive && "Cannot increment an invalid or end iterator.");
                row++;
                if (row >= iter.count())
                {
                    find_next_valid_batch();
                }
                return *this;
            }

            auto operator*() const
            {
                assert(alive && "Cannot dereference an invalid or end iterator.");
                assert(row < iter.count() && "Row index out of bounds for current batch.");

                flecs::entity e = iter.entity(row);

                auto comps = get_components_tuple(
                    std::index_sequence_for<Components...>{}
                );

                return std::tuple_cat(
                    std::make_tuple(e),
                    comps
                );
            }
        };

        Iterator begin() { return Iterator{ world, query }; }
        Iterator end() const { return Iterator{}; }

        [[nodiscard]] std::size_t size() const
        {
            return query.count();
        }


        auto operator[](std::size_t index) const
        {
            assert(index < size() && "Index out of bounds");

            std::size_t current_index = 0;
            std::optional<std::tuple<flecs::entity, Components&...>> result;

            query.each([&](flecs::entity e, Components&... comps)
            {
                if (current_index == index)
                {
                    // Use std::tie to create a tuple of references
                    result = std::tuple<flecs::entity, Components&...>(e, comps...);
                    return false;
                }
                current_index++;
                return true;
            });

            assert(result.has_value() && "Failed to find element at index");
            return result.value();
        }
    };
}