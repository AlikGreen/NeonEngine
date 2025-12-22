#include "sceneGraphWindow.h"

#include <imgui.h>

#include "core/engine.h"
#include "core/sceneManager.h"
#include "core/components/parentComponent.h"
#include "core/components/tagComponent.h"
#include "graphics/components/camera.h"
#include "graphics/components/pointLight.h"
#include "imgui/imGuiExtensions.h"

namespace Neon::Editor
{
    SceneGraphWindow::SceneGraphWindow()
        : ImGuiWindow("Scene Graph") {  }

    void SceneGraphWindow::render()
    {
        Scene& scene = Engine::getSceneManager().getCurrentScene();

        const float lineHeight = ImGui::GetFrameHeight();
        if (ImGui::Button("+", ImVec2(lineHeight, lineHeight)))
        {
            ImGui::OpenPopup("AddEntityPopup");
        }

        if (ImGui::BeginPopup("AddEntityPopup"))
        {
            if (ImGui::MenuItem("Entity"))
            {
                scene.createEntity("New Entity");
                ImGui::CloseCurrentPopup();
            }

            if (ImGui::MenuItem("Camera"))
            {
                ECS::Entity entity = scene.createEntity("New Camera");
                entity.emplace<Camera>();
                ImGui::CloseCurrentPopup();
            }

            if (ImGui::MenuItem("Point Light"))
            {
                ECS::Entity entity = scene.createEntity("New Point Light");
                entity.emplace<PointLight>();
                ImGui::CloseCurrentPopup();
            }

            ImGui::EndPopup();
        }

        ImGui::SameLine();

        ImGui::SetNextItemWidth(-FLT_MIN);
        ImGui::InputTextWithHint("##search", "Search...", &search);

        if (ImGui::IsWindowHovered() && ImGui::IsMouseDown(0) && !ImGui::IsAnyItemHovered())
        {
            m_selected = std::nullopt;
        }

        buildChildrenMap();

        for (const auto entity : m_rootEntities)
        {
            drawEntityNode(entity);
        }

        if(m_pendingDelete.has_value())
        {
            if(m_selected == m_pendingDelete)
                m_selected = std::nullopt;
            scene.getRegistry().destroy(m_pendingDelete.value());
            m_pendingDelete = std::nullopt;
        }
    }

    std::optional<ECS::Entity> SceneGraphWindow::getSelectedEntity()
    {
        return m_selected;
    }

    void SceneGraphWindow::buildChildrenMap()
    {
        m_childrenMap.clear();
        m_rootEntities.clear();

        auto& registry = Engine::getSceneManager().getCurrentScene().getRegistry();

        for (auto [e, p] : registry.view<Parent>())
        {
            if (!p.hasParent())
                m_rootEntities.push_back(e);
            else
                m_childrenMap[p.getParent()].push_back(e);
        }
    }

    std::string toLower(const std::string& str)
    {
        std::string result = str;

        std::ranges::transform(
            result,
            result.begin(),
            [](const unsigned char c)
            {
                return static_cast<char>(std::tolower(c));
            });

        return result;
    }

    void SceneGraphWindow::drawEntityNode(const ECS::Entity e)
    {
        auto& world = Engine::getSceneManager().getCurrentScene().getRegistry();

        const auto it = m_childrenMap.find(e);
        const bool hasChildren = (it != m_childrenMap.end() && !it->second.empty());

        const std::string label = "⬡ " + world.get<Tag>(e).name;

        const bool searched = !search.empty() && toLower(world.get<Tag>(e).name).contains(toLower(search));

        ImGui::PushID(static_cast<int>(e.getId()));

        ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow
            | ImGuiTreeNodeFlags_SpanAvailWidth;

        if (!hasChildren)
        {
            flags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
        }

        if (m_selected == e)
        {
            flags |= ImGuiTreeNodeFlags_Selected;
        }

        ImVec2 framePadding = ImGui::GetStyle().FramePadding;
        framePadding.x = 2.0f;
        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, framePadding);

        if(searched)
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.392, 0.478, 0.729, 1.0f));

        const bool open = ImGui::TreeNodeEx("##node", flags, "%s", label.c_str());

        if(searched)
            ImGui::PopStyleColor();

        ImGui::PopStyleVar();


        if (ImGui::BeginPopupContextItem("EntityContext"))
        {
            if (ImGui::MenuItem("Delete"))
            {
                m_pendingDelete = e;
            }

            ImGui::EndPopup();
        }
        else if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen())
        {
            m_selected = e;
        }

        if (hasChildren)
        {
            if (open)
            {
                for (const ECS::Entity c : it->second)
                {
                    drawEntityNode(c);
                }
                ImGui::TreePop();
            }
        }

        ImGui::PopID();
    }
}
