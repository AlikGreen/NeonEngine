#include "scriptRuntimeInterface.h"

namespace Neon::Scripting
{
    ScriptRuntimeInterface createRuntimeInterface()
    {
        return ScriptRuntimeInterface{
            .input = {
                .isKeyHeld = ExportedAPI::Input::isKeyHeld,
                .isKeyPressed = ExportedAPI::Input::isKeyPressed,
                .isKeyReleased = ExportedAPI::Input::isKeyReleased
            },
            .ecs = {
                .registerComponentType = ExportedAPI::EntitySystem::registerComponentType,
                .createEntity = ExportedAPI::EntitySystem::createEntity,
                .addComponent = ExportedAPI::EntitySystem::addComponent,
                .createView = ExportedAPI::EntitySystem::createView,
                .getViewSize = ExportedAPI::EntitySystem::getViewSize,
                .getViewEntry = ExportedAPI::EntitySystem::getViewEntry,
                .getTypeHash = ExportedAPI::EntitySystem::getTypeHash
            },
            .scene = {
                .getCurrentScene = ExportedAPI::SceneAccess::getCurrentScene,
                .getSceneRegistry = ExportedAPI::SceneAccess::getSceneRegistry
            },
            .components = {
                .Tag_getName = ExportedAPI::ComponentAccessors::Tag_getName,
                .Tag_setName = ExportedAPI::ComponentAccessors::Tag_setName
            }
        };
    }
}