#pragma once

#include "scriptBridge.h"

namespace Neon::Scripting
{
    // Interface that the script runtime receives
    struct ScriptRuntimeInterface
    {
        // Input subsystem
        struct
        {
            bool (*isKeyHeld)(int key);
            bool (*isKeyPressed)(int key);
            bool (*isKeyReleased)(int key);
        } input;

        // Entity-Component System operations
        struct
        {
            void (*registerComponentType)(ECS::Registry*, size_t typeHash, size_t size, size_t alignment);
            size_t (*createEntity)(ECS::Registry*);
            void* (*addComponent)(ECS::Registry*, size_t entity, size_t typeHash, void* data);

            ECS::ViewBase* (*createView)(ECS::Registry*, size_t* types, size_t count);
            size_t (*getViewSize)(ECS::ViewBase*);
            Interop::EntityComponentData* (*getViewEntry)(ECS::ViewBase*, size_t index);

            size_t (*getTypeHash)(const char* typeName);
        } ecs;

        // Scene management
        struct
        {
            Scene* (*getCurrentScene)();
            ECS::Registry* (*getSceneRegistry)(Scene*);
        } scene;

        // Component accessors
        struct
        {
            const char* (*Tag_getName)(Tag*);
            void (*Tag_setName)(Tag*, const char*);
        } components;
    };

    // Factory to create the interface
    ScriptRuntimeInterface createRuntimeInterface();
}
