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
        src/graphics/backend/vertexInputState.h)

target_include_directories(neonEngine PRIVATE "${CMAKE_SOURCE_DIR}/src")
target_link_libraries(neonEngine PUBLIC SDL3::SDL3 glm::glm shaderc spirv-cross-c)