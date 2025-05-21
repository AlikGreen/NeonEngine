#include "gameSystem.h"

#include <iostream>

#include "asset/assetHandle.h"
#include "asset/assetManager.h"
#include "audio/audioManager.h"
#include "core/engine.h"
#include "ecs/ecsSystem.h"
#include "graphics/components/meshRenderer.h"
#include "input/events/keyDownEvent.h"
#include "input/events/mouseButtonDownEvent.h"
#include "input/events/textInputEvent.h"

void GameSystem::postStartup()
{
    auto* ecsSystem = Neon::Engine::getInstance()->getSystem<Neon::ECSSystem>();
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

    const Neon::AssetHandle meshHandle = Neon::AssetManager::loadAsset<Neon::Mesh>("models/cube.glb");
    meshRenderer.mesh = Neon::AssetManager::getAsset<Neon::Mesh>(meshHandle);

    meshRenderer.mesh->apply();

    Neon::AudioManager::playSound(R"(C:\Users\alikg\CLionProjects\neonEngine\sandboxApp\resources\city-bgm-336601.mp3)");
}

void GameSystem::update()
{
    frameCount++;
    auto end = std::chrono::high_resolution_clock::now();
    if (std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() > 1000)
    {
        std::cout << frameCount << std::endl;
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
