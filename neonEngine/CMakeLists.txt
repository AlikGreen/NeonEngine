cmake_minimum_required(VERSION 3.29)
project(neonEngine)

set(CMAKE_CXX_STANDARD 23)

add_library(neonEngine SHARED src/neonEngine.cpp
        src/neonEngine.h
        src/rendering/window.cpp
        src/rendering/window.h
        src/core/system.h
        src/core/event.h
        src/rendering/renderSystem.cpp
        src/rendering/renderSystem.h)
