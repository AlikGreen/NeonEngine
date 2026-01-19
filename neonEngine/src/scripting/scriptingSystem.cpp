#include "scriptingSystem.h"

#include <iostream>
#include <windows.h>

#include <neonECS/neonECS.h>

#include "core/engine.h"
#include "core/sceneManager.h"
#include "input/input.h"
#include "timers/scopeTimer.h"

namespace Neon
{
    struct RegistryComponentPack
    {
        size_t entityId;
        size_t componentCount;
        const void* components;
    };

    using IsKeyFn = bool(*)(int);
    using GetRegistryFn = ECS::Registry*(*)();
    using RegisterTypeFn = void(*)(ECS::Registry*, size_t, size_t, size_t);
    using ViewIterNextFn = RegistryComponentPack*(*)(ECS::ViewBase*);
    using GetViewFn = ECS::ViewBase*(*)(ECS::Registry*, size_t*, size_t);
    using CreateEntityFn = size_t(*)(ECS::Registry*);
    using EmplaceComponentFn = void(*)(ECS::Registry*, size_t, size_t, void*);

    struct Callbacks
    {
        IsKeyFn is_key_held;
        IsKeyFn is_key_pressed;
        IsKeyFn is_key_released;

        RegisterTypeFn register_type;
        GetRegistryFn get_registry;
        ViewIterNextFn view_iter_next;
        GetViewFn get_view;
        CreateEntityFn create_entity;
        EmplaceComponentFn emplace_component;
    };

    // V lang interop api
    extern "C"
    {
        bool native_isKeyHeld(int key)
        {
            return Input::isKeyHeld(static_cast<KeyCode>(key));
        }

        bool native_isKeyPressed(int key)
        {
            return Input::isKeyPressed(static_cast<KeyCode>(key));
        }

        bool native_isKeyReleased(int key)
        {
            return Input::isKeyReleased(static_cast<KeyCode>(key));
        }

        void native_registerType(ECS::Registry* reg, const size_t type, const size_t size, const size_t alignment)
        {
            reg->registerType(type, size, alignment);
        }

        ECS::Registry* native_getRegistry()
        {
            return &Engine::getSceneManager().getCurrentScene().getRegistry();
        }

        RegistryComponentPack* native_viewIterNext(ECS::ViewBase* viewPtr)
        {
            if (!viewPtr) return nullptr;
            auto* view = dynamic_cast<ECS::TypeErasedView*>(viewPtr);
            if(!view->next())
                return nullptr;

            const ECS::TypeErasedView::ComponentPack& pack = view->current();  // Reference, not copy

            auto* registryPack = new RegistryComponentPack();
            registryPack->entityId = pack.entityId;
            registryPack->components = pack.components.data();  // Now safe - points to m_cachedPack
            registryPack->componentCount = pack.components.size();

            return registryPack;
        }

        ECS::ViewBase* native_getView(ECS::Registry* reg, size_t* types, const size_t numTypes)
        {
            if(reg == nullptr) return nullptr;
            const std::vector typeVec(types, types + numTypes);
            return  &reg->viewTypeErased(typeVec);
        }

        size_t native_createEntity(ECS::Registry* reg)
        {
            return reg->createEntity().getId();
        }

        void native_emplaceComponent(ECS::Registry* reg, size_t entity, size_t componentType, void* data)
        {
            ECS::StorageBase& storage = reg->storageTypeErased(componentType);
            storage.emplaceOpaquePtr(entity, data);
        }
    }

    void ScriptingSystem::startup()
    {
        int result = 0;

        {
            Debug::ScopeTimer<std::chrono::milliseconds> timer("V script compilation");

            std::string basePath = "C:/Users/alikg/CLionProjects/NeonEngine";
            std::string vExe     = Path::join(basePath, "neonEngine/dependencies/v/bin/windows/v.exe");
            std::string scriptDir   = Path::join(basePath, "neonEngine/sdk/modules/neon");

            std::stringstream cmd;

            cmd << vExe;

            cmd << " -enable-globals";
            cmd << " -shared";
            cmd << " -g";
            cmd << " -cc tcc"; // -prod for optimization / gcc
            cmd << " -d no_backtrace";
            cmd << " -o scripts.dll";

            cmd << " " << scriptDir;

            result = std::system(cmd.str().c_str());
        }

        Debug::ensure(result == 0, "Failed to compile script");

        if (result == 0)
            Log::info("V compilation successful!");
        else
            Log::error("Error compiling V script!");

        {
            Debug::ScopeTimer<std::chrono::milliseconds> timer("V script load");
            m_scriptLib = LoadLibraryA("scripts.dll");
            if (!m_scriptLib) return;


            std::function vFnRegisterCbs = getFunction<void, void*>("native_register_callbacks");
            m_vFnUpdate = getFunction<void>("native_update");

            auto* cbs = new Callbacks();
            cbs->is_key_held = native_isKeyHeld;
            cbs->is_key_pressed = native_isKeyPressed;
            cbs->is_key_released = native_isKeyReleased;

            cbs->register_type = native_registerType;
            cbs->get_registry = native_getRegistry;
            cbs->view_iter_next = native_viewIterNext;
            cbs->get_view = native_getView;
            cbs->create_entity = native_createEntity;
            cbs->emplace_component = native_emplaceComponent;

            vFnRegisterCbs(cbs);
        }
    }

    void ScriptingSystem::update()
    {
        m_vFnUpdate();
    }

    void ScriptingSystem::shutdown()
    {
        FreeLibrary(m_scriptLib);
    }
}
