#pragma once
#include "entityID.h"

namespace Neon
{
    class EntityManager
    {
    public:
        EntityID createEntity(uint32_t worldIndex)
        {
            EntityID id;

            if (availableEntities.empty())
            {
                id = EntityID(nextEntityID++, worldIndex);
            } else
            {
                id = EntityID(availableEntities.back(), worldIndex);
                availableEntities.pop_back();
            }

            ++livingEntityCount;
            return id;
        }

        void destroyEntity(const EntityID entity)
        {
            if (!entity.isValid()) return;

            availableEntities.push_back(entity.getEntityId());
            --livingEntityCount;
        }

        [[nodiscard]] uint32_t getLivingEntityCount() const
        {
            return livingEntityCount;
        }

        [[nodiscard]] EntityManager clone() const
        {
            EntityManager cloned;
            cloned.availableEntities = availableEntities;
            cloned.livingEntityCount = livingEntityCount;
            cloned.nextEntityID = nextEntityID;
            return cloned;
        }
    private:
        friend class World;
        std::vector<uint32_t> availableEntities;
        uint32_t livingEntityCount = 0;
        uint32_t nextEntityID = 1;
    };
}
