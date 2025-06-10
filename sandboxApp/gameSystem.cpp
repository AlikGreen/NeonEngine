#include "gameSystem.h"

#include <iostream>
#include <tiny_gltf.h>

#include "asset/assetHandle.h"
#include "asset/assetManager.h"
#include "audio/audioManager.h"
#include "core/engine.h"
#include "debug/logger.h"
#include "ecs/ecsSystem.h"
#include "ecs/components/transformComponent.h"
#include "graphics/components/camera.h"
#include "graphics/components/meshRenderer.h"
#include "graphics/components/pointLight.h"
#include "input/input.h"
#include "input/events/keyDownEvent.h"
#include "input/events/textInputEvent.h"

void GameSystem::postStartup()
{
    auto* ecsSystem = Neon::Engine::getSystem<Neon::ECSSystem>();
    const auto world = ecsSystem->getWorld();

    // Cube entity
    Neon::Entity entity = world->createEntity();
    entity.addComponent<Neon::MeshRenderer>();
    auto& meshRenderer = entity.getComponent<Neon::MeshRenderer>();

    meshRenderer.material = new Neon::Material();
    meshRenderer.material->albedo = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
    meshRenderer.material->roughness = 0.5f;

    Neon::AssetManager& assetManager = Neon::Engine::getAssetManager();
    const Neon::AssetHandle meshHandle = assetManager.loadAsset<Neon::Mesh>("models/sphere.glb");
    meshRenderer.mesh = meshHandle;

    // Player/Camera entity
    Neon::Entity cameraEntity = world->createEntity();
    cameraEntity.addComponent<Neon::Camera>();
    auto& camTransform = cameraEntity.getComponent<Neon::Transform>();
    camTransform.setPosition({0, 0, -5});

    // Light entity
    Neon::Entity lightEntity = world->createEntity();
    auto& lightTransform = lightEntity.getComponent<Neon::Transform>();
    lightTransform.setPosition({2, 5, 0});

    lightEntity.addComponent<Neon::PointLight>();
    auto& pointLight = lightEntity.getComponent<Neon::PointLight>();
    pointLight.power = 1.0f;

    // const Neon::AssetHandle songHandle = assetManager->loadAsset<Neon::AudioClip>("city-bgm-336601.mp3");
    // auto *song = assetManager->getAsset<Neon::AudioClip>(songHandle);
    // Neon::Engine::getAudioManager()->playSound(song);

    Neon::Input::setCursorLocked(true);
    Neon::Input::setCursorVisible(false);
}

void GameSystem::update()
{
    const auto world = Neon::Engine::getSystem<Neon::ECSSystem>()->getWorld();

    const auto cameras = world->getComponents<Neon::Camera, Neon::Transform>();
    if(cameras.size() < 1) return;
    auto [camEntity, camera, camTransform] = cameras[0];

    constexpr float cameraSpeed = 0.0005f;

    if(Neon::Input::isKeyHeld(KeyCode::W)) { camTransform.translate(camTransform.forward()*cameraSpeed); }
    if(Neon::Input::isKeyHeld(KeyCode::A)) { camTransform.translate(camTransform.left()*cameraSpeed); }
    if(Neon::Input::isKeyHeld(KeyCode::S)) { camTransform.translate(camTransform.backward()*cameraSpeed); }
    if(Neon::Input::isKeyHeld(KeyCode::D)) { camTransform.translate(camTransform.right()*cameraSpeed); }
    if(Neon::Input::isKeyHeld(KeyCode::Space)) { camTransform.translate(camTransform.up()*cameraSpeed); }
    if(Neon::Input::isKeyHeld(KeyCode::LShift)) { camTransform.translate(camTransform.down()*cameraSpeed); }

    constexpr float cameraSens = 0.0005f;
    camTransform.rotate(glm::vec3(Neon::Input::getMouseDelta().y, Neon::Input::getMouseDelta().x, 0)*cameraSens);
}

void GameSystem::event(Neon::Event *event)
{

}
