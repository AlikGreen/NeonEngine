cmake_minimum_required(VERSION 3.29)
project(neonRHI)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(${CMAKE_SOURCE_DIR}/../neonEngine/dependencies/glm ${CMAKE_BINARY_DIR}/dependencies/glm)
add_subdirectory(${CMAKE_SOURCE_DIR}/../neonEngine/dependencies/spirv-cross ${CMAKE_BINARY_DIR}/dependencies/spirv-cross)
add_subdirectory(${CMAKE_SOURCE_DIR}/../neonEngine/dependencies/shaderc ${CMAKE_BINARY_DIR}/dependencies/shaderc)
add_subdirectory(${CMAKE_SOURCE_DIR}/../neonEngine/dependencies/glfw ${CMAKE_BINARY_DIR}/dependencies/glfw)
add_subdirectory(${CMAKE_SOURCE_DIR}/../neonEngine/dependencies/glad ${CMAKE_BINARY_DIR}/dependencies/glad)

file(GLOB_RECURSE
        SRC_FILES
        CONFIGURE_DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
)

add_library(neonRHI STATIC ${SRC_FILES}
        src/sampler.h
        src/implementations/opengl/samplerOGL.cpp
        src/implementations/opengl/samplerOGL.h
        src/descriptions/samplerDescription.h)

target_compile_definitions(neonRHI PRIVATE GLFW_INCLUDE_NONE)

target_include_directories(neonRHI PUBLIC src/)
target_include_directories(neonRHI PUBLIC include/)
target_link_libraries(neonRHI PUBLIC glfw glm::glm shaderc spirv-cross-c glad)