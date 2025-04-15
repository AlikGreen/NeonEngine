cmake_minimum_required(VERSION 3.29)
project(neonEngine)

set(CMAKE_CXX_STANDARD 23)

set(WINDOWS_SDK_VERSION "10.0.26100.0")  # Update this to your SDK version
set(WINDOWS_SDK_PATH "C:/Program Files (x86)/Windows Kits/10/Include/${WINDOWS_SDK_VERSION}")

# Include Windows SDK headers before MinGW's headers
include_directories(BEFORE SYSTEM "${WINDOWS_SDK_PATH}/um")
include_directories(BEFORE SYSTEM "${WINDOWS_SDK_PATH}/shared")

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

set(NVRHI_WITH_DX11 ON CACHE BOOL "Enable DX11 backend")
set(NVRHI_WITH_DX12 OFF CACHE BOOL "Disable DX12 backend")
set(NVRHI_WITH_VULKAN OFF BOOL "Disable Vulkan backend")

add_subdirectory(dependencies/nvrhi)

add_subdirectory(dependencies/glfw)

add_library(neonEngine SHARED
        src/neonEngine.cpp
        src/neonEngine.h
        src/rendering/window.cpp
        src/rendering/window.h
        src/core/system.h
        src/core/event.h
        src/rendering/renderSystem.cpp
        src/rendering/renderSystem.h
        src/rendering/messageCallback.h)


target_link_libraries(neonEngine PRIVATE nvrhi nvrhi_d3d11 d3d11)
#target_include_directories(neonEngine PRIVATE "dependencies/nvrhi/include")

target_link_libraries(neonEngine PRIVATE glfw)
target_include_directories(neonEngine PRIVATE "dependencies/glfw/include")