#include "gameWindow.h"

#include <imgui.h>

#include "core/engine.h"
#include "core/sceneManager.h"
#include "graphics/components/camera.h"
#include "imgui/imGuiExtensions.h"

namespace Neon::Editor
{

    void GameWindow::render()
    {
        ImGui::Begin("Game");
        auto& world = Engine::getSceneManager().getCurrentScene().getRegistry();
        const auto cameras = world.view<Camera>();

        const ImVec2 avail = ImGui::GetContentRegionAvail();

        if(cameras.size() >= 1)
        {
            auto [camEntity, camera] = cameras.at(0);
            if(camera.renderTarget != nullptr)
            {
                camera.setAspectRatio(static_cast<float>(avail.x) / static_cast<float>(avail.y));
                const Rc<RHI::TextureView> sceneTexture = camera.renderTarget->getColorAttachment();
                NeonGui::Image(sceneTexture, avail, ImVec2(0, 1), ImVec2(1, 0));
                camera.renderTarget->resize(static_cast<uint32_t>(avail.x), static_cast<uint32_t>(avail.y));
            }
        }
        ImGui::End();

    }
}
