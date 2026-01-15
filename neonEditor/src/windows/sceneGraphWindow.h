#pragma once
#include <optional>
#include <unordered_set>
#include <neonECS/neonECS.h>

#include "editorWindow.h"

namespace Neon::Editor
{
class SceneGraphWindow final : public EditorWindow
{
public:
    void render() override;
private:
    void buildChildrenMap();

    void drawEntityNode(ECS::Entity e);

    std::optional<ECS::Entity> m_pendingDelete{};
    std::unordered_map<ECS::Entity, std::vector<ECS::Entity>> m_childrenMap{};
    std::vector<ECS::Entity> m_rootEntities{};
    std::unordered_set<size_t> m_expandedEntities{};
    std::string search{};
};
}
