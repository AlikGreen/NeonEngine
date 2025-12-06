#pragma once
#include <neonECS/neonECS.h>


namespace Neon
{
    class Prefab;

    class Scene
{
public:
    [[nodiscard]] ECS::Registry& getRegistry();
    ECS::Entity createEntity(const std::string& name = "Entity");
    void import(Prefab* entity);
private:
    ECS::Registry registry = ECS::Registry();
};
}
