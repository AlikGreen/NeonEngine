cmake_minimum_required(VERSION 3.29)
project(neonEngine)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(dependencies/SDL3)
set(SDL_SHARED_DEFAULT OFF FORCE)
set(SDL_STATIC_DEFAULT ON FORCE)

add_subdirectory(dependencies/glm)
add_subdirectory(dependencies/shaderc)
add_subdirectory(dependencies/spirv-cross)

set(FLECS_SHARED OFF FORCE)
set(FLECS_STATIC ON FORCE)
add_subdirectory(dependencies/flecs)

set(TINYGLTF_HEADER_ONLY OFF CACHE BOOL "Build tinygltf as a library" FORCE)
add_subdirectory(dependencies/tinygltf)

add_subdirectory(dependencies/miniaudio)

add_library(neonEngine STATIC
        src/core/engine.cpp
        src/core/engine.h
        src/graphics/backend/window.cpp
        src/graphics/backend/window.h
        src/core/system.h
        src/core/event.h
        src/graphics/renderSystem.cpp
        src/graphics/renderSystem.h
        src/graphics/backend/shader.cpp
        src/graphics/backend/shader.h
        src/util/file.cpp
        src/graphics/backend/BackendAPIEnum.h
        src/graphics/backend/physicalDevice.cpp
        src/graphics/backend/physicalDevice.h
        src/graphics/backend/graphicsPipeline.cpp
        src/graphics/backend/graphicsPipeline.h
        src/graphics/backend/vertexInputState.cpp
        src/graphics/backend/vertexInputState.h
        src/graphics/backend/buffers/vertexBuffer.h
        src/graphics/backend/buffers/transferBuffer.h
        src/graphics/backend/buffers/transferBuffer.cpp
        src/graphics/backend/commandBuffer.cpp
        src/graphics/backend/commandBuffer.h
        src/graphics/backend/renderPass.cpp
        src/graphics/backend/renderPass.h
        src/core/eventManager.cpp
        src/core/eventManager.h
        src/graphics/backend/colorTarget.cpp
        src/graphics/backend/colorTarget.h
        src/input/keyCodes.h
        src/input/events/keyDownEvent.h
        src/input/events/keyUpEvent.h
        src/input/events/mouseButtonUpEvent.h
        src/input/events/mouseButtonDownEvent.h
        src/input/events/textInputEvent.h
        src/graphics/backend/texture.cpp
        src/graphics/backend/texture.h
        src/ecs/world.cpp
        src/ecs/world.h
        src/ecs/ecsSystem.cpp
        src/ecs/ecsSystem.h
        src/ecs/entity.h
        src/graphics/components/meshRenderer.h
        src/graphics/mesh.cpp
        src/graphics/mesh.h
        src/asset/assetManager.cpp
        src/asset/assetManager.h
        src/asset/asset.h
        src/asset/streams/assetStream.h
        src/graphics/backend/depthState.cpp
        src/graphics/backend/depthState.h
        src/graphics/backend/depthStencilTarget.cpp
        src/graphics/backend/depthStencilTarget.h
        src/graphics/backend/convertSDL.cpp
        src/graphics/backend/convertSDL.h
        src/graphics/backend/renderTargetsDescription.h
        src/ecs/components/transformComponent.h
        src/ecs/components/tagComponent.h
        src/ecs/entity.h
        src/ecs/entity.cpp
        src/ecs/componentList.h
        src/ecs/typeSet.h
        src/common.h
        src/debug/logger.cpp
        src/debug/logger.h
        src/debug/logLevel.h
        src/debug/scopeTimer.cpp
        src/debug/scopeTimer.h
        src/debug/assert.cpp
        src/debug/assert.h
        src/debug/assertAction.h
        src/asset/assetHandle.h
        src/asset/assetHandle.h
        src/audio/audioManager.cpp
        src/audio/audioManager.h
        src/audio/audioClip.cpp
        src/audio/audioClip.h
        src/audio/soundHandle.cpp
        src/audio/soundHandle.h
        src/audio/audioSystem.cpp
        src/audio/audioSystem.h
        src/audio/audioCommand.h)

target_link_options(neonEngine
        INTERFACE
        -static
        -static-libgcc
        -static-libstdc++
)

set(CMAKE_PCH_INSTANTIATE_TEMPLATES ON)
target_precompile_headers(neonEngine PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src/common.h")

target_include_directories(neonEngine PUBLIC src/)
target_link_libraries(neonEngine PUBLIC tinygltf SDL3::SDL3 glm::glm shaderc spirv-cross-c flecs_static miniaudio)