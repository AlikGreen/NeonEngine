#pragma once

namespace Neon
{
    struct Tag;
    class Scene;
}

namespace Neon::ECS
{
    class ViewBase;
    class Registry;
}

namespace Neon::Scripting
{
    // Data structures for marshaling between C++ and scripts
    namespace Interop
    {
        struct EntityComponentData
        {
            size_t entityId;
            size_t componentCount;
            const void* componentPtrs;
        };
    }

    // C API boundary - functions exported to script runtime
    namespace ExportedAPI
    {
        namespace Input
        {
            extern "C"
            {
                bool isKeyHeld(int key);
                bool isKeyPressed(int key);
                bool isKeyReleased(int key);
            }
        }

        namespace EntitySystem
        {
            extern "C"
            {
                void registerComponentType(ECS::Registry* reg, size_t typeHash, size_t size, size_t alignment);
                size_t createEntity(ECS::Registry* reg);
                void* addComponent(ECS::Registry* reg, size_t entity, size_t componentTypeHash, void* componentData);

                ECS::ViewBase* createView(ECS::Registry* reg, size_t* typeHashes, size_t count);
                size_t getViewSize(ECS::ViewBase* view);
                Interop::EntityComponentData* getViewEntry(ECS::ViewBase* view, size_t index);

                size_t getTypeHash(const char* typeName);
            }
        }

        namespace SceneAccess
        {
            extern "C"
            {
                Scene* getCurrentScene();
                ECS::Registry* getSceneRegistry(Scene* scene);
            }
        }

        // Component-specific accessors
        namespace ComponentAccessors
        {
            extern "C"
            {
                const char* Tag_getName(Tag* component);
                void Tag_setName(Tag* component, const char* name);
            }
        }
    }
}