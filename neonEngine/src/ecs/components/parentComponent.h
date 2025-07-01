#pragma once
#include "ecs/entityID.h"

namespace Neon
{
    class Parent
    {
    public:
        [[nodiscard]] bool hasParent() const
        {
            return parent.isValid();
        }

        [[nodiscard]] EntityID getParent() const
        {
            return parent;
        }

        void setParent(const EntityID parent)
        {
            this->parent = parent;
        }
    private:
        EntityID parent{};
    };
}