#include "scriptBridge.h"

#include <neonECS/neonECS.h>

#include "log.h"
#include "core/scene.h"
#include "core/engine.h"
#include "core/sceneManager.h"
#include "core/components/tagComponent.h"
#include "core/components/transformComponent.h"
#include "graphics/components/camera.h"
#include "graphics/components/meshRenderer.h"
#include "input/input.h"

namespace Neon::Scripting::ExportedAPI
{
    namespace Input
    {
        extern "C"
        {
            bool isKeyHeld(int key)
            {
                return Neon::Input::isKeyHeld(static_cast<KeyCode>(key));
            }

            bool isKeyPressed(int key)
            {
                return Neon::Input::isKeyPressed(static_cast<KeyCode>(key));
            }

            bool isKeyReleased(int key)
            {
                return Neon::Input::isKeyReleased(static_cast<KeyCode>(key));
            }
        }
    }

    namespace EntitySystem
    {
        extern "C"
        {
            void registerComponentType(ECS::Registry* reg, size_t typeHash, size_t size, size_t alignment)
            {
                reg->registerType(typeHash, size, alignment);
            }

            size_t createEntity(ECS::Registry* reg)
            {
                return reg->createEntity().getId();
            }

            void* addComponent(ECS::Registry* reg, size_t entity, size_t componentTypeHash, void* componentData)
            {
                ECS::StorageBase& storage = reg->storageTypeErased(componentTypeHash);
                return storage.emplaceOpaquePtr(entity, componentData);
            }

            ECS::ViewBase* createView(ECS::Registry* reg, size_t* typeHashes, size_t count)
            {
                if (reg == nullptr) return nullptr;

                const std::vector<size_t> typeVec(typeHashes, typeHashes + count);
                return &reg->viewTypeErased(typeVec);
            }

            size_t getViewSize(ECS::ViewBase* view)
            {
                auto* typedView = dynamic_cast<ECS::TypeErasedView*>(view);
                return typedView ? typedView->size() : 0;
            }

            Interop::EntityComponentData* getViewEntry(ECS::ViewBase* view, size_t index)
            {
                if (!view)
                {
                    Log::error("View pointer is null");
                    return nullptr;
                }

                auto* typedView = dynamic_cast<ECS::TypeErasedView*>(view);
                if (!typedView)
                {
                    Log::error("Failed to cast view to TypeErasedView");
                    return nullptr;
                }

                if (index >= typedView->size())
                {
                    Log::error("Index {} out of bounds for view of size {}", index, typedView->size());
                    return nullptr;
                }

                const ECS::TypeErasedView::ComponentPack& entry = typedView->at(index);
                auto* result = new Interop::EntityComponentData{
                    .entityId = entry.entityId,
                    .componentCount = entry.components.size(),
                    .componentPtrs = entry.components.data()
                };

                return result;
            }

            size_t getTypeHash(const char* typeName)
            {
                const std::string name(typeName);

                if (name == "Transform")
                    return typeid(Transform).hash_code();
                if (name == "Camera")
                    return typeid(Camera).hash_code();
                if (name == "MeshRenderer")
                    return typeid(MeshRenderer).hash_code();
                if (name == "Tag")
                    return typeid(Tag).hash_code();

                Log::error("Unknown component type: {}", name);
                return 0;
            }
        }
    }

    namespace SceneAccess
    {
        extern "C"
        {
            Scene* getCurrentScene()
            {
                return &Engine::getSceneManager().getCurrentScene();
            }

            ECS::Registry* getSceneRegistry(Scene* scene)
            {
                return &scene->getRegistry();
            }
        }
    }

    namespace ComponentAccessors
    {
        extern "C"
        {
            const char* Tag_getName(Tag* component)
            {
                return component->name.c_str();
            }

            void Tag_setName(Tag* component, const char* name)
            {
                Log::info("Tag set: {}", name);
                component->name = name;
            }
        }
    }
}