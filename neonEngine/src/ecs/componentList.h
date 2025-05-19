#pragma once
#include <stdexcept>
#include <tuple>
#include <cassert>
#include <flecs.h>
// #include "entity.h" // Make sure this is included if Neon::Entity is a custom type

namespace Neon
{
    template<typename... Components>
    class ComponentList
    {
        flecs::world&                 world_; // Non-const reference to the world
        flecs::query<Components...>   q_;     // The query object, stored by value

    public:
        ComponentList(flecs::world& world, flecs::query<Components...> q)
            : world_(world)
            , q_(std::move(q)) // q is passed by value, then moved into the member q_
        { }

        class iterator
        {
            ecs_iter_t  iter_data_; // Stores the raw C iterator state. Must be declared before it_
            flecs::iter it_;        // Flecs C++ convenience wrapper for &iter_data_
            bool        alive_;     // True if iterator is on a valid entity in a non-empty batch
            std::size_t row_;       // Current entity index within the current batch (0 to it_.count()-1)

            // Helper to get components for the current entity (row_) in the current batch
            template<std::size_t... Is>
            auto get_components_tuple(std::index_sequence<Is...>) const
            {
                // it_.template field_at<ComponentType>(field_index, entity_index_in_batch)
                return std::tuple<Components&...> {
                    (it_.template field_at<Components>(Is, row_))...
                };
            }

            // Advances 'it_' (which operates on 'iter_data_') to the next batch
            // that contains actual entities (it_.count() > 0).
            // Sets 'alive_' and 'row_' appropriately.
            void find_next_valid_batch() {
                // it_.next() calls the C function ecs_query_next (or ecs_iter_next)
                // on the underlying iter_data_.
                while (it_.next()) { // Advances to the next table/batch
                    if (it_.count() > 0) { // Check if this batch has entities
                        alive_ = true;
                        row_ = 0; // Reset row to the start of the new batch
                        return;
                    }
                    // If it_.count() is 0, this batch is empty; loop again to try the next one.
                }
                alive_ = false; // No more non-empty batches were found
            }

        public:
            // Constructor for begin()
            // Takes world by non-const ref, query by const ref.
            iterator(flecs::world& world_ref, const flecs::query<Components...>& query_ref)
              : iter_data_( ecs_query_iter(world_ref.c_ptr(), query_ref.c_ptr()) ) // Initialize C iterator
              , it_(&iter_data_)      // Point flecs::iter wrapper to our iter_data_
              , alive_(false)         // Will be set by find_next_valid_batch
              , row_(0)               // Will be set by find_next_valid_batch
            {
                find_next_valid_batch(); // Prime the iterator: find the first non-empty batch
            }

            // Default constructor for end() - represents an exhausted or invalid iterator
            iterator()
              : iter_data_{}, it_{nullptr}, alive_(false), row_(0)
            { }

            bool operator!=(const iterator& other) const {
                // For range-based for loops, comparison is typically with a default-constructed 'end' iterator.
                // 'alive_' status is sufficient for this.
                return alive_ != other.alive_;
            }

            iterator& operator++()
            {
                assert(alive_ && "Cannot increment an invalid or end iterator.");
                row_++; // Advance to the next entity in the current batch
                if (row_ >= it_.count()) // Check if we've moved past the end of the current batch
                {
                    // Current batch is exhausted, find the next non-empty one
                    find_next_valid_batch();
                }
                return *this;
            }

            auto operator*() const
            {
                assert(alive_ && "Cannot dereference an invalid or end iterator.");
                // This assertion should be guaranteed if alive_ is true due to find_next_valid_batch()
                assert(row_ < it_.count() && "Row index out of bounds for current batch.");

                flecs::entity e = it_.entity(row_);

                auto comps = get_components_tuple(
                    std::index_sequence_for<Components...>{}
                );

                // If Neon::Entity is a wrapper for flecs::entity:
                // return std::tuple_cat(std::make_tuple(Neon::Entity(e)), comps);
                return std::tuple_cat(
                    std::make_tuple(e), // Using flecs::entity directly
                    comps
                );
            }
        }; // End class iterator

        // begin() is non-const because it uses the non-const world_ member.
        iterator begin() { return iterator{ world_, q_ }; }
        // end() can be const as it creates a default (empty) iterator.
        iterator end() const { return iterator{}; }
    }; // End class ComponentList
} // End namespace Neon