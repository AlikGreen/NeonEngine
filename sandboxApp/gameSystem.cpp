#include "gameSystem.h"

#define GLM_ENABLE_EXPERIMENTAL
#include "core/components/transformComponent.h"
#include "glm/gtx/string_cast.hpp"
#include "neonEngine/neonEngine.h"

void GameSystem::postStartup()
{
    auto& scene = Neon::Engine::getSceneManager().getCurrentScene();
    auto& world = scene.getRegistry();

    Neon::AssetManager& assetManager = Neon::Engine::getAssetManager();
    const Neon::AssetHandle modelHandle = assetManager.loadAsset<Neon::Prefab>("models/monkey.glb");
    const auto model = assetManager.getAsset<Neon::Prefab>(modelHandle);

    Neon::ECS::Entity modelEntity = scene.import(model);
    modelEntity.get<Neon::Transform>().setScale(glm::vec3(1.0f));

    // Player/Camera entity
    Neon::ECS::Entity cameraEntity = scene.createEntity();
    cameraEntity.emplace<Neon::Camera>();
    auto& camTransform = cameraEntity.get<Neon::Transform>();
    camTransform.setPosition({0, 0, 0});

    // Light entity
    Neon::ECS::Entity lightEntity = scene.createEntity();
    auto& lightTransform = lightEntity.get<Neon::Transform>();
    lightTransform.setPosition({8, 10, 8});

    lightEntity.emplace<Neon::PointLight>();
    auto& pointLight = lightEntity.get<Neon::PointLight>();
    pointLight.power = 10.0f;
    pointLight.color = glm::vec3(1.0f, 1.0f, 1.0f);

    // const Neon::AssetHandle songHandle = assetManager->loadAsset<Neon::AudioClip>("city-bgm-336601.mp3");
    // auto *song = assetManager->getAsset<Neon::AudioClip>(songHandle);
    // Neon::Engine::getAudioManager()->playSound(song);


    Neon::Input::setCursorLocked(true);
    Neon::Input::setCursorVisible(false);

    start = std::chrono::high_resolution_clock::now();
}

void GameSystem::update()
{
    auto& world = Neon::Engine::getSceneManager().getCurrentScene().getRegistry();

    const auto cameras = world.view<Neon::Camera, Neon::Transform>();
    if(cameras.size() < 1) return;
    auto [camEntity, camera, camTransform] = cameras.at(0);

    constexpr float cameraSpeed = 0.0005f;
    glm::vec3 dir{0.0f};

    if(Neon::Input::isKeyHeld(KeyCode::W)) dir += glm::vec3(camTransform.forward().x, 0, camTransform.forward().z);
    if(Neon::Input::isKeyHeld(KeyCode::S)) dir += glm::vec3(camTransform.backward().x, 0, camTransform.backward().z);
    if(Neon::Input::isKeyHeld(KeyCode::A)) dir += glm::vec3(camTransform.left().x, 0, camTransform.left().z);
    if(Neon::Input::isKeyHeld(KeyCode::D)) dir += glm::vec3(camTransform.right().x, 0, camTransform.right().z);

    if(Neon::Input::isKeyHeld(KeyCode::Space)) { dir.y += 1; }
    if(Neon::Input::isKeyHeld(KeyCode::LShift)) { dir.y -= 1; }

    camTransform.translate(dir * cameraSpeed);
    // camTransform.translate({0, -1*cameraSpeed, 0});
    // if(camTransform.getPosition().y < 0) camTransform.setPosition({camTransform.getPosition().x, 0, camTransform.getPosition().z});

    constexpr float cameraSens = 0.0005f;
    camTransform.rotate(glm::vec3(Neon::Input::getMouseDelta().y, Neon::Input::getMouseDelta().x, 0)*cameraSens);

    const std::chrono::time_point<std::chrono::high_resolution_clock> end = std::chrono::high_resolution_clock::now();

    frameCount++;

    if(end - start >= std::chrono::seconds(5))
    {
        Neon::Log::info("FPS: {}", frameCount/5);
        start = end;
        frameCount = 0;
    }
}

void GameSystem::event(Neon::Event *event)
{

}
