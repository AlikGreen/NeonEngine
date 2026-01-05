#pragma once
#include <imgui_internal.h>
#include <vector>

#include "asset/assetManager.h"

namespace Neon::Editor
{
class AssetsWindow final
{
public:
    void render();
    void dropFile(std::string filepath);
private:
    std::vector<std::string> droppedPaths;
    AssetID hoveredAssetId = AssetID::invalid();
    double hoverStartTime = 0.0;

    void consumeFileDropInRect(const ImRect &rect);
};
}
