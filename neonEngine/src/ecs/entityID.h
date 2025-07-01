#pragma once
#include <cstdint>

namespace Neon
{
class EntityID
{
public:
    static EntityID None;

    EntityID() noexcept = default;
    EntityID(const uint32_t entityId, const uint32_t worldId) : entityId(entityId), worldId(worldId) {  }

    [[nodiscard]] uint32_t getEntityId() const { return entityId; }
    [[nodiscard]] uint32_t getWorldId() const { return worldId; }

    auto operator<=>(const EntityID& other) const = default;
    bool operator==(   const EntityID& other) const = default;

    [[nodiscard]] bool isValid() const
    {
        return entityId != 0;
    }
private:
    uint32_t entityId;
    uint32_t worldId;
};
}

template <>
struct std::hash<Neon::EntityID>
{
    size_t operator()(const Neon::EntityID& id) const noexcept
    {
        const size_t h1 = std::hash<uint32_t>{}(id.getEntityId());
        const size_t h2 = std::hash<uint32_t>{}(id.getWorldId());
        return h1 ^ (h2 << 1);
    }
};
