#pragma once
#include <imgui_internal.h>
#include <vector>

#include "asset/assetHandle.h"

namespace Neon::Editor
{
class AssetsWindow final
{
public:
    void render();
    void dropFile(std::string filepath);
private:
    std::vector<std::string> droppedPaths;
    AssetHandle hoveredAssetId = 0;
    double hoverStartTime = 0.0;

    void consumeFileDropInRect(const ImRect &rect);
};
}
