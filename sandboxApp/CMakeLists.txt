cmake_minimum_required(VERSION 3.29)
project(sandboxApp)

set(CMAKE_CXX_STANDARD 23)

add_executable(sandboxApp
        main.cpp
        gameSystem.cpp
        gameSystem.h)

add_subdirectory(${CMAKE_SOURCE_DIR}/../neonEngine ${CMAKE_BINARY_DIR}/neonEngine)
target_link_libraries(sandboxApp PRIVATE neonEngine)
target_include_directories(sandboxApp PRIVATE "${CMAKE_SOURCE_DIR}/../neonEngine/src")

add_custom_command(TARGET sandboxApp POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "$<TARGET_FILE:neonEngine>"
        "${CMAKE_BINARY_DIR}/libneonEngine.dll"
        COMMENT "Copying DLL to the build directory as neonEngine.dll"
)