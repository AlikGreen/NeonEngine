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
    ECS::Entity import(Prefab& prefab);
private:
    ECS::Registry registry = ECS::Registry();
};
}
