#include "editorSystem.h"

#define GLM_ENABLE_EXPERIMENTAL
#include "core/components/transformComponent.h"
#include "glm/gtx/string_cast.hpp"
#include "graphics/imGuiSystem.h"
#include "graphics/events/dropFileEvent.h"
#include "neonEngine/neonEngine.h"
#include "windows/assetsWindow.h"

namespace Neon::Editor
{
    void EditorSystem::startup()
    {
        auto& scene = Engine::getSceneManager().getCurrentScene();

        AssetManager& assetManager = Engine::getAssetManager();
        const AssetHandle modelHandle = assetManager.loadAsset<Prefab>("models/testScene.glb");
        auto& model = assetManager.getAsset<Prefab>(modelHandle);

        ECS::Entity modelEntity = scene.import(model);
        modelEntity.get<Transform>().setScale(glm::vec3(0.05f));

        // Player/Camera entity
        ECS::Entity cameraEntity = scene.createEntity();
        auto& camera = cameraEntity.emplace<Camera>();
        camera.matchWindowSize = false;
        auto& camTransform = cameraEntity.get<Transform>();
        camTransform.setPosition({0, 0, 0});

        // Light entity
        ECS::Entity lightEntity = scene.createEntity();
        auto& lightTransform = lightEntity.get<Transform>();
        lightTransform.setPosition({8, 10, 8});

        lightEntity.emplace<PointLight>();
        auto& pointLight = lightEntity.get<PointLight>();
        pointLight.power = 10.0f;
        pointLight.color = glm::vec3(1.0f, 1.0f, 1.0f);

    }

    void EditorSystem::update()
    {

    }

    void EditorSystem::event(Event* event)
    {
        if(const auto* windowEvent = dynamic_cast<DropFileEvent*>(event))
        {
            const Rc<AssetsWindow> assetsWindow = Engine::getSystem<ImGuiSystem>()->getWindow<AssetsWindow>();

            assetsWindow->dropFile(windowEvent->getPath());
        }
    }
}