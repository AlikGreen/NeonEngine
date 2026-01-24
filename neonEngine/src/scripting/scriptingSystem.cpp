#include "scriptingSystem.h"

#include <iostream>

#ifdef _WIN32
#include <windows.h>
#else
#include <dlfcn.h>
#endif

#include <neonECS/neonECS.h>

#include "scriptRuntimeInterface.h"
#include "core/engine.h"
#include "core/sceneManager.h"
#include "core/components/tagComponent.h"
#include "core/components/transformComponent.h"
#include "graphics/components/camera.h"
#include "graphics/components/meshRenderer.h"
#include "timers/scopeTimer.h"
#include "log.h"

namespace Neon
{
    void ScriptingSystem::startup()
    {
        auto& registry = Engine::getSceneManager().getCurrentScene().getRegistry();
        registry.registerType<Transform>();
        registry.registerType<Camera>();
        registry.registerType<Tag>();
        registry.registerType<MeshRenderer>();

        {
            Debug::ScopeTimer<std::chrono::milliseconds> timer("Script runtime load");

            const auto dllPath = R"(C:\Users\alikg\CLionProjects\NeonEngine\neonEngine\sdk\d\bin\neon.dll)";

            m_runtimeHandle = LoadLibraryA(dllPath);

            Debug::ensure(m_runtimeHandle != nullptr, "Unable to load script runtime library");

            // Load required functions from the runtime
            auto registerCallbacksFn = loadFunction<void, void*>("native_registerCallbacks");
            auto loadDllFn = loadFunction<void, const char*>("native_loadLib");
            m_updateCallback = loadFunction<void>("native_update");

            Debug::ensure(m_updateCallback != nullptr, "Failed to find 'native_update' in script runtime");

            // Pass interface to the script runtime
            Scripting::ScriptRuntimeInterface scriptInterface = Scripting::createRuntimeInterface();
            Log::info("Callbacks size: {}", sizeof(Scripting::ScriptRuntimeInterface));
            registerCallbacksFn(&scriptInterface);

            loadDllFn(R"(C:\Users\alikg\CLionProjects\NeonEngine\neonEditor\resources\scripts\bin\neon_editor.dll)");
        }
    }

    void ScriptingSystem::update()
    {
        if (m_updateCallback)
        {
            m_updateCallback();
        }
    }

    void ScriptingSystem::shutdown()
    {
        if (m_runtimeHandle)
        {
            FreeLibrary(m_runtimeHandle);
            m_runtimeHandle = nullptr;
        }
    }
}