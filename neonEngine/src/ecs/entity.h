#pragma once

#include "flecs.h"


namespace Neon
{
    class Entity
    {
    public:
        Entity(const flecs::entity entity) : handle(entity) { }

        operator flecs::entity() const { return handle; }

        template<typename T, typename... Args>
        void addComponent(Args&&... args)
        {
            handle.emplace<T>(std::forward<Args>(args)...);
        }

        template<typename T>
        [[nodiscard]] bool hasComponent() const
        {
            return handle.has<T>();
        }

        template<typename T>
        T& getComponent() const
        {
            auto ptr = handle.get_ref<T>();
            assert(ptr.get() != nullptr);
            return *ptr.get();
        }
    private:
        flecs::entity handle;
    };
}
