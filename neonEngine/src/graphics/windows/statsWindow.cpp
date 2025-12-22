#include "statsWindow.h"

#include <imgui.h>

namespace Neon
{
    StatsWindow::StatsWindow()
        : ImGuiWindow("Stats") {  }

    void StatsWindow::render()
    {
        ImGui::Text("Stats");
    }
}
