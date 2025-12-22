#include "viewportWindow.h"
#include "imgui/imGuiExtensions.h"

#include <imgui.h>

#include "core/engine.h"
#include "core/sceneManager.h"
#include "graphics/components/camera.h"

namespace Neon
{
    ViewportWindow::ViewportWindow()
        : ImGuiWindow("Viewport") {  }

    void ViewportWindow::render()
    {
        auto& world = Engine::getSceneManager().getCurrentScene().getRegistry();
        const auto cameras = world.view<Camera>();

        const ImVec2 avail = ImGui::GetContentRegionAvail();

        Rc<RHI::TextureView> sceneTexture = nullptr;
        if(cameras.size() >= 1)
        {
            auto [camEntity, camera] = cameras.at(0);
            camera.setWidth(static_cast<uint32_t>(avail.x));
            camera.setHeight(static_cast<uint32_t>(avail.y));
            sceneTexture = camera.getColorTexture();
        }

        NeonGui::Image(sceneTexture, avail, ImVec2(0, 1), ImVec2(1, 0));
    }
}
