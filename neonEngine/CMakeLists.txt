cmake_minimum_required(VERSION 3.29)
project(neonEngine)

set(CMAKE_CXX_STANDARD 23)


# Include Windows SDK headers before MinGW's headers
include_directories(BEFORE SYSTEM "${WINDOWS_SDK_PATH}/um")
include_directories(BEFORE SYSTEM "${WINDOWS_SDK_PATH}/shared")

add_subdirectory(dependencies/SDL3)
add_subdirectory(dependencies/glm)
add_subdirectory(dependencies/shaderc)
add_subdirectory(dependencies/spirv-cross)

add_library(neonEngine SHARED
        src/neonEngine.cpp
        src/neonEngine.h
        src/graphics/backend/window.cpp
        src/graphics/backend/window.h
        src/core/system.h
        src/core/event.h
        src/graphics/renderSystem.cpp
        src/graphics/renderSystem.h
        src/graphics/backend/shader.cpp
        src/graphics/backend/shader.h
        src/util/file.cpp
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
        src/core/ecs/world.cpp
        src/core/ecs/world.h
        src/core/ecs/ecsSystem.cpp
        src/core/ecs/ecsSystem.h
        src/core/ecs/component.h
        src/core/ecs/componentList.cpp
        src/core/ecs/componentList.h
        src/core/ecs/entity.h)

target_include_directories(neonEngine PUBLIC src/)
target_link_libraries(neonEngine PUBLIC SDL3::SDL3 glm::glm shaderc spirv-cross-c)