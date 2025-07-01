#include "sceneManager.h"

namespace Neon
{
    SceneManager::SceneManager()
    {
        currentScene = Engine::getAssetManager().addAsset(new Scene());
    }

    Scene& SceneManager::getCurrentScene() const
    {
        return *currentScene;
    }
}
