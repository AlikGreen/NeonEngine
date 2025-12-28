#include "assetsWindow.h"

#include <imgui.h>
#include <imgui_internal.h>
#include <util/file.h>

#include "asset/assetManager.h"
#include "graphics/imGuiSystem.h"
#include "graphics/loaders/prefabLoaderGLB.h"

struct ImRect;

namespace Neon::Editor
{
    void AssetsWindow::consumeFileDropInRect(const ImRect& rect)
    {
        AssetManager& assetManager = Engine::getAssetManager();

        for (const auto& path : droppedPaths)
        {
            const ImVec2 p = ImGui::GetMousePos();

            if (rect.Contains(p))
            {
                std::string ext = File::getFileExtension(path);

                if(ext == "glb")
                {
                    assetManager.loadAsset<PrefabLoaderGLB>(path);
                    Log::info("Loaded Prefab {}", path);
                }

            }
        }

        droppedPaths.clear();
    }


    void AssetsWindow::render()
    {
        AssetManager& assetManager = Engine::getAssetManager();

        static ImGuiTextFilter assetFilter;
        static AssetHandle selectedAssetId = 0;

        static AssetHandle hoveredAssetId = 0;
        static double hoverStartTime = 0.0;

        ImGui::Begin("Assets");

        assetFilter.Draw("Search", 220.0f);
        ImGui::Separator();

        ImGui::BeginChild("##assetGrid", ImVec2(0.0f, 0.0f), true, ImGuiWindowFlags_HorizontalScrollbar);

        {
            const ImVec2 winPos = ImGui::GetWindowPos();
            const ImVec2 winSize = ImGui::GetWindowSize();
            const ImRect dropRect(winPos, ImVec2(winPos.x + winSize.x, winPos.y + winSize.y));
            consumeFileDropInRect(dropRect);
        }

        const auto assetHandles = assetManager.getAllAssetHandles();
        if (assetHandles.empty())
        {
            ImGui::TextDisabled("No assets found.");
            ImGui::TextDisabled("Drag .glb files here to import.");
            ImGui::EndChild();
            return;
        }

        constexpr float padding = 8.0f;
        constexpr float tileSize = 96.0f;

        const float textHeight = ImGui::GetTextLineHeight();
        const float spacingY = 6.0f;
        const float tileHeight = tileSize + spacingY + textHeight + 6.0f;

        const float availX = ImGui::GetContentRegionAvail().x;
        int columns = static_cast<int>((availX + padding) / (tileSize + padding));
        if (columns < 1)
        {
            columns = 1;
        }

        ImGui::PushStyleVar(ImGuiStyleVar_CellPadding, ImVec2(padding * 0.5f, padding * 0.5f));
        ImGui::PushFont(ImGuiSystem::smallFont);

        if (ImGui::BeginTable("##assetGridTable", columns, ImGuiTableFlags_SizingFixedFit))
        {
            for (AssetHandle assetId : assetHandles)
            {
                const std::string assetName = assetManager.getName(assetId);
                if (!assetFilter.PassFilter(assetName.c_str()))
                {
                    continue;
                }

                ImGui::TableNextColumn();
                ImGui::PushID(static_cast<size_t>(assetId));

                const bool isSelected = (selectedAssetId == assetId);

                ImGui::InvisibleButton("##tile", ImVec2(tileSize, tileHeight));

                const bool isHovered = ImGui::IsItemHovered();
                const bool isClicked = ImGui::IsItemClicked(ImGuiMouseButton_Left);

                if (isClicked)
                {
                    selectedAssetId = assetId;
                }

                const ImVec2 rectMin = ImGui::GetItemRectMin();
                const ImVec2 rectMax = ImGui::GetItemRectMax();

                ImDrawList* drawList = ImGui::GetWindowDrawList();

                const ImU32 bgCol = ImGui::GetColorU32((isSelected || isHovered) ? ImGuiCol_FrameBgHovered : ImGuiCol_WindowBg);
                const ImU32 borderCol = ImGui::GetColorU32(ImGuiCol_Border);

                drawList->AddRectFilled(rectMin, rectMax, bgCol, 4.0f);
                drawList->AddRect(rectMin, rectMax, borderCol, 4.0f);

                const ImVec2 imgMin = ImVec2(rectMin.x + 3.0f, rectMin.y + 3.0f);
                const ImVec2 imgMax = ImVec2(imgMin.x + tileSize - 6.0f, imgMin.y + tileSize - 6.0f);

                // ImTextureID previewTex = assetManager.getPreviewTexture(assetId);
                // if (previewTex != nullptr)
                // {
                //     drawList->AddImage(previewTex, imgMin, imgMax);
                // }
                // else
                // {
                    drawList->AddRectFilled(imgMin, imgMax, ImGui::GetColorU32(ImGuiCol_FrameBg), 2.0f);
                // }

                const ImVec2 textPos = ImVec2(rectMin.x + 4.0f, imgMax.y + spacingY);
                const float textMaxX = rectMax.x - 4.0f;

                const float nameAvail = textMaxX - textPos.x;
                const bool isNameTruncated = (ImGui::CalcTextSize(assetName.c_str()).x > nameAvail);

                ImGui::PushClipRect(rectMin, rectMax, true);
                drawList->AddText(textPos, ImGui::GetColorU32(ImGuiCol_Text), assetName.c_str());
                ImGui::PopClipRect();

                if (isHovered)
                {
                    const double now = ImGui::GetTime();
                    if (hoveredAssetId != assetId)
                    {
                        hoveredAssetId = assetId;
                        hoverStartTime = now;
                    }

                    if (isNameTruncated && (now - hoverStartTime) >= 1.0)
                    {
                        ImGui::BeginTooltip();
                        ImGui::TextUnformatted(assetName.c_str());
                        ImGui::EndTooltip();
                    }
                }
                else if (hoveredAssetId == assetId)
                {
                    hoveredAssetId = 0;
                }

                if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceAllowNullID))
                {
                    ImGui::SetDragDropPayload("ASSET_ID", &assetId, sizeof(assetId));
                    ImGui::TextUnformatted(assetName.c_str());
                    ImGui::EndDragDropSource();
                }

                if (ImGui::BeginPopupContextItem())
                {
                    if (ImGui::MenuItem("Delete"))
                    {
                        Log::error("Deleting assets not implemented");
                    }
                    ImGui::EndPopup();
                }

                ImGui::PopID();
            }

            ImGui::EndTable();
        }
        ImGui::PopFont();

        ImGui::PopStyleVar();
        ImGui::EndChild();
        ImGui::End();
    }


    void AssetsWindow::dropFile(std::string filepath)
    {
        droppedPaths.emplace_back(filepath);
        Log::info("Dropped file: {}", filepath);
    }
}
