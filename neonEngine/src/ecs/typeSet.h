#pragma once
#include <typeindex>
#include <unordered_set>

namespace Neon
{
    class TypeSet
    {
    public:
        explicit TypeSet(const std::unordered_set<std::type_index> &types) : types(types)
        {

        }

        bool has(const std::type_index type) const
        {
            return types.contains(type);
        }

        bool operator==(const TypeSet& other) const
        {
            for (auto type: types)
            {
                if(!other.has(type))
                {
                    return false;
                }
            }

            return true;
        }

        std::unordered_set<std::type_index> getTypes() const
        {
            return types;
        }

    private:
        std::unordered_set<std::type_index> types;
    };
}

namespace std
{
    template<>
    struct hash<Neon::TypeSet>
    {
        size_t operator()(Neon::TypeSet const& s) const noexcept
        {
            size_t seed = 0;
            for (auto const& ti : s.getTypes())
            {
                seed ^= ti.hash_code()
                      + 0x9e3779b97f4a7c15ULL
                      + (seed << 6)
                      + (seed >> 2);
            }
            return seed;
        }
    };
}