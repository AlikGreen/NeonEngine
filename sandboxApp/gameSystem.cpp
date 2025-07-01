#include "gameSystem.h"

#include "neonEngine/neonEngine.h"

void GameSystem::postStartup()
{
    auto& world = Neon::Engine::getSceneManager().getCurrentScene().getWorld();

    Neon::AssetManager& assetManager = Neon::Engine::getAssetManager();
    const Neon::AssetHandle modelHandle = assetManager.loadAsset<Neon::Prefab>("models/sponza.glb");
    const auto* model = assetManager.getAsset<Neon::Prefab>(modelHandle);

    world.merge(model->world);

    auto prefabs = world.getComponents<Neon::PrefabComponent, Neon::Transform>();
    for (auto [entity, prefab, transform]: prefabs)
    {
        transform.setScale(glm::vec3(0.001f));
    }


    // Player/Camera entity
    Neon::Entity cameraEntity = world.createEntity();
    cameraEntity.addComponent<Neon::Camera>();
    auto& camTransform = cameraEntity.getComponent<Neon::Transform>();
    camTransform.setPosition({0, 0, 0});

    // Light entity
    Neon::Entity lightEntity = world.createEntity();
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
    auto& world = Neon::Engine::getSceneManager().getCurrentScene().getWorld();

    const auto cameras = world.getComponents<Neon::Camera, Neon::Transform>();
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
