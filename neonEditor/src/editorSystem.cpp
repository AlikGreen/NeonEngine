#include "editorSystem.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <imgui_internal.h>

#include "core/components/tagComponent.h"
#include "core/components/transformComponent.h"
#include "glm/gtx/string_cast.hpp"
#include "graphics/imGuiSystem.h"
#include "graphics/events/dropFileEvent.h"
#include "imgui/imGuiExtensions.h"
#include "neonEngine/neonEngine.h"
#include "windows/assetsWindow.h"
#include "windows/propertiesWindow.h"
#include "windows/sceneGraphWindow.h"
#include "windows/viewportWindow.h"

namespace Neon::Editor
{
    void EditorSystem::startup()
    {
        auto& scene = Engine::getSceneManager().getCurrentScene();

        AssetManager& assetManager = Engine::getAssetManager();
        const AssetHandle modelHandle = assetManager.loadAsset<Prefab>("models/monkey.glb");
        auto& model = assetManager.getAsset<Prefab>(modelHandle);

        ECS::Entity modelEntity = scene.import(model);
        modelEntity.get<Tag>().name = "Imported model";
        modelEntity.get<Transform>().setScale(glm::vec3(1.0f));

        // Player/Camera entity
        ECS::Entity cameraEntity = scene.createEntity("Main Camera");
        auto& camera = cameraEntity.emplace<Camera>();
        camera.matchWindowSize = false;
        auto& camTransform = cameraEntity.get<Transform>();
        camTransform.setPosition({0, 0, 0});

        // Light entity
        ECS::Entity lightEntity = scene.createEntity("Light");
        auto& lightTransform = lightEntity.get<Transform>();
        lightTransform.setPosition({8, 10, 8});

        lightEntity.emplace<PointLight>();
        auto& pointLight = lightEntity.get<PointLight>();
        pointLight.power = 10.0f;
        pointLight.color = glm::vec3(1.0f, 1.0f, 1.0f);

        auto* imGuiSystem = Engine::getSystem<ImGuiSystem>();

        imGuiSystem->shouldDrawDockSpace = true;
        imGuiSystem->shouldDrawConsole = true;
        imGuiSystem->shouldDrawStats = true;

        imGuiSystem->addRenderCallback([this]()
        {
            viewportWindow.render();
            sceneGraphWindow.render();
            propertiesWindow.render();
            assetsWindow.render();
        });
    }

    void EditorSystem::update()
    {

    }

    void EditorSystem::event(Event* event)
    {
        if(const auto* windowEvent = dynamic_cast<DropFileEvent*>(event))
        {
            assetsWindow.dropFile(windowEvent->getPath());
        }
    }
}
