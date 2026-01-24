module scene_management.scene_manager;

import scene_management.scene;

private alias GetCurrentSceneFn = void* function();
private alias GetRegistryFn = void* function(void*);

struct SceneCallbacks
{
    extern (C) void* function() getCurrentScene;
    extern (C) void* function(void*) getSceneRegistry;
}

static class SceneManager
{
    private static SceneCallbacks callbacks;

    public static void setCallbacks(SceneCallbacks callbacks)
    {
        this.callbacks = callbacks;
    }

    public static Scene getCurrentScene()
    {
        void* nativeScene = callbacks.getCurrentScene();
        void* registryPtr = callbacks.getSceneRegistry(nativeScene);
        return new Scene(registryPtr);
    }
}
