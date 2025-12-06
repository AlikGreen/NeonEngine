#pragma once
#include <neonECS/neonECS.h>

namespace Neon
{
    class Parent
    {
    public:
        [[nodiscard]] bool hasParent() const
        {
            return parent.has_value();
        }

        [[nodiscard]] ECS::Entity getParent() const
        {
            return parent.value();
        }

        void setParent(const ECS::Entity parent)
        {
            this->parent = parent;
        }
    private:
        std::optional<ECS::Entity> parent;
    };
}