#include "scriptingSystem.h"

#include <iostream>
#include <windows.h>

#include <neonECS/neonECS.h>

#include "core/engine.h"
#include "core/sceneManager.h"
#include "core/components/tagComponent.h"
#include "core/components/transformComponent.h"
#include "graphics/components/camera.h"
#include "graphics/components/meshRenderer.h"
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

        RegistryComponentPack* native_getViewAt(ECS::ViewBase* viewPtr, size_t index)
        {
            if (!viewPtr)
            {
                Log::error("viewPtr is null\n");
                return nullptr;
            }

            const auto* view = dynamic_cast<ECS::TypeErasedView*>(viewPtr);
            if (!view)
            {
                Log::error("dynamic_cast failed\n");
                return nullptr;
            }

            if(index >= view->size())
            {
                Log::error("index greater than view size\n");
                return nullptr;
            }

            const ECS::TypeErasedView::ComponentPack pack = view->at(index);
            auto* registryPack = new RegistryComponentPack();
            registryPack->entityId = pack.entityId;
            registryPack->components = pack.components.data();
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

        size_t native_getViewSize(ECS::ViewBase* viewPtr)
        {
            return dynamic_cast<ECS::TypeErasedView*>(viewPtr)->size();
        }

        void* native_emplaceComponent(ECS::Registry* reg, size_t entity, size_t componentType, void* data)
        {
            ECS::StorageBase& storage = reg->storageTypeErased(componentType);
            return storage.emplaceOpaquePtr(entity, data);
        }

        size_t native_getCppTypeHash(const char* typeName)
        {
            // Convert C++ type name to hash_code
            // You need to map string names to actual type_info
            const std::string name(typeName);

            if (name == "Transform")
                return typeid(Transform).hash_code();
            if (name == "Camera")
                return typeid(Camera).hash_code();
            if (name == "MeshRenderer")
                return typeid(MeshRenderer).hash_code();
            if (name == "Tag")
                return typeid(Tag).hash_code();

            Log::error("Unknown native component type: " + name);
            return 0;
        }

        const char* native_tagGetName(void* tag)
        {
            return static_cast<Tag*>(tag)->name.c_str();
        }

        void native_tagSetName(void* tag, const char* name)
        {
            Log::info("Tag set: {}", name);
            static_cast<Tag*>(tag)->name = name;
        }
    }

    using TagGetName = const char*(*)(void*);
    using TagSetName = void(*)(void*, const char*);

    struct TagCallbacks
    {
        TagGetName getName = native_tagGetName;
        TagSetName setName = native_tagSetName;
    };

    using RegistryRegisterTypeFn = void(*)(ECS::Registry*, size_t, size_t, size_t);
    using RegistryGetViewFn = ECS::ViewBase*(*)(ECS::Registry*, size_t*, size_t);
    using RegistryCreateEntityFn = size_t(*)(ECS::Registry*);
    using RegistryEmplaceComponentFn = void*(*)(ECS::Registry*, size_t, size_t, void*);
    using GetCppTypeHash = size_t(*)(const char*);

    using ViewGetAtFn = RegistryComponentPack*(*)(ECS::ViewBase*, size_t);
    using ViewGetSizeFn = size_t(*)(ECS::ViewBase*);

    struct RegistryCallbacks
    {
        GetCppTypeHash getCppTypeHash = native_getCppTypeHash;

        RegistryRegisterTypeFn registerType = native_registerType;
        RegistryGetViewFn getView = native_getView;
        RegistryCreateEntityFn createEntity = native_createEntity;
        RegistryEmplaceComponentFn emplaceComponent = native_emplaceComponent;

        ViewGetAtFn viewGetAt = native_getViewAt;
        ViewGetSizeFn viewGetSize = native_getViewSize;
    };

    using IsKeyFn = bool(*)(int);

    struct InputCallbacks
    {
        IsKeyFn isKeyHeld = native_isKeyHeld;
        IsKeyFn isKeyPressed = native_isKeyPressed;
        IsKeyFn isKeyReleased = native_isKeyReleased;
    };

    using GetRegistryFn = ECS::Registry*(*)();

    struct Callbacks
    {
        GetRegistryFn getRegistry = native_getRegistry;

        InputCallbacks* inputCallbacks = new InputCallbacks();
        RegistryCallbacks* registryCallbacks = new RegistryCallbacks();
        TagCallbacks* tagCallbacks = new TagCallbacks();
    };

    void ScriptingSystem::startup()
    {
        auto& registry = Engine::getSceneManager().getCurrentScene().getRegistry();
        registry.registerType<Transform>();
        registry.registerType<Camera>();
        registry.registerType<Tag>();
        registry.registerType<MeshRenderer>();

        {
            Debug::ScopeTimer<std::chrono::milliseconds> timer("script load");
            const char* dllPath = R"(C:\Users\alikg\CLionProjects\NeonEngine\neonEngine\sdk\d\Neon\bin\neon.dll)";
            m_scriptLib = LoadLibraryA(dllPath);
            Debug::ensure(m_scriptLib != nullptr, "Unable to load script library");

            const std::function vFnRegisterCbs = getFunction<void, void*>("native_registerCallbacks");
            m_vFnUpdate = getFunction<void>("native_update");
            Debug::ensure(m_vFnUpdate != nullptr, "Can't find native native_update");

            auto* cbs = new Callbacks();
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
