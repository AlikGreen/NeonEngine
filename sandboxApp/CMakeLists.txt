cmake_minimum_required(VERSION 3.29)
project(sandboxApp)

set(CMAKE_CXX_STANDARD 23)

add_executable(sandboxApp
        main.cpp
        gameSystem.cpp
        gameSystem.h)

add_subdirectory(${CMAKE_SOURCE_DIR}/../neonEngine ${CMAKE_BINARY_DIR}/neonEngine)
target_link_libraries(sandboxApp PRIVATE neonEngine)