#include "gameSystem.h"

#include <iostream>

#include "asset/assetHandle.h"
#include "asset/assetManager.h"
#include "audio/audioManager.h"
#include "core/engine.h"
#include "debug/logger.h"
#include "ecs/ecsSystem.h"
#include "graphics/components/meshRenderer.h"
#include "input/events/keyDownEvent.h"
#include "input/events/mouseButtonDownEvent.h"
#include "input/events/textInputEvent.h"

void GameSystem::postStartup()
{
    auto* ecsSystem = Neon::Engine::getSystem<Neon::ECSSystem>();
    const auto world = ecsSystem->getWorld();
    Neon::Entity entity = world->createEntity();
    entity.addComponent<Neon::MeshRenderer>();
    auto& meshRenderer = entity.getComponent<Neon::MeshRenderer>();

    // meshRenderer.mesh = Neon::makeRef<Neon::Mesh>();
    // meshRenderer.mesh->vertices =
    // {
    //     {{-0.5, -0.5, 0.1}, {1, 0, 0}, {-0.5, -0.5}},
    //     {{0.5, -0.5, 0.1}, {0, 1, 0}, {0.5, -0.5}},
    //     {{0, 0.5, 0.1}, {0, 0, 1}, {0, 0.5}}
    // };
    //
    // meshRenderer.mesh->indices = { 0, 1, 2 };

    Neon::AssetManager* assetManager = Neon::Engine::getAssetManager();
    const Neon::AssetHandle meshHandle = assetManager->loadAsset<Neon::Mesh>("models/cube.glb");
    meshRenderer.mesh = Neon::Engine::getAssetManager()->getAsset<Neon::Mesh>(meshHandle);
    meshRenderer.mesh->apply();

    Neon::AssetHandle songHandle = assetManager->loadAsset<Neon::AudioClip>("city-bgm-336601.mp3");
    Neon::Ref<Neon::AudioClip> song = assetManager->getAsset<Neon::AudioClip>(songHandle);

    Neon::Engine::getAudioManager()->playSound(song);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    Neon::Engine::getAudioManager()->playSound(song);
    // std::this_thread::sleep_for(std::chrono::milliseconds(500));
    // Neon::Engine::getAudioManager()->playSound(song);
}

void GameSystem::update()
{
    frameCount++;
    auto end = std::chrono::high_resolution_clock::now();
    if (std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() > 1000)
    {
        Neon::Logger::info("GameSystem", "frames per second: "+frameCount);
        start = std::chrono::high_resolution_clock::now();
        frameCount = 0;
    }
}

void GameSystem::event(Neon::Event *event)
{
    if(const auto keyDownEvent = dynamic_cast<Neon::KeyDownEvent*>(event))
    {
        std::cout << std::to_string(static_cast<uint32_t>(keyDownEvent->getKeycode())) << std::endl;
    }
    else if(const auto mouseDownEvent = dynamic_cast<Neon::MouseButtonDownEvent*>(event))
    {
        std::cout << std::to_string(static_cast<uint32_t>(mouseDownEvent->getButton())) << std::endl;
    }

    if(const auto textInputEvent = dynamic_cast<Neon::TextInputEvent*>(event))
    {
        std::cout << textInputEvent->getText() << std::endl;
    }
}
