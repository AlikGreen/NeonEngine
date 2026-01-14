#pragma once
#include <neonECS/neonECS.h>


namespace Neon
{
class Scene
{
public:
    [[nodiscard]] ECS::Registry& getRegistry();
    ECS::Entity createEntity(const std::string& name = "Entity");
    ECS::Entity import(Scene& scene);
    std::string name;
private:
    friend class SceneSerializer;
    ECS::Registry registry = ECS::Registry();
};
}
