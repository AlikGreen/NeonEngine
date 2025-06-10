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
add_subdirectory(dependencies/glad)

file(GLOB_RECURSE
        SRC_FILES
        CONFIGURE_DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
)

add_library(neonEngine STATIC ${SRC_FILES}
        src/asset/assetSerializer.h
        src/graphics/MeshSerializerGLB.cpp
        src/graphics/MeshSerializerGLB.h)

target_link_options(neonEngine
        INTERFACE
        -static
        -static-libgcc
        -static-libstdc++
)

set(CMAKE_PCH_INSTANTIATE_TEMPLATES ON)
target_precompile_headers(neonEngine PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src/common.h")

target_include_directories(neonEngine PUBLIC src/)
target_link_libraries(neonEngine PUBLIC tinygltf SDL3::SDL3 glm::glm shaderc spirv-cross-c flecs_static miniaudio glad)