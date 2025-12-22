#pragma once
#include <imgui_internal.h>
#include <vector>

#include "asset/assetHandle.h"
#include "graphics/windows/imGuiWindow.h"

namespace Neon::Editor
{
class AssetsWindow final : public ImGuiWindow
{
public:
    AssetsWindow();

    void render() override;
    void dropFile(const char* filepath);
private:
    std::vector<std::string> droppedPaths;
    AssetHandle hoveredAssetId = 0;
    double hoverStartTime = 0.0;

    void consumeFileDropInRect(const ImRect &rect);
};
}
