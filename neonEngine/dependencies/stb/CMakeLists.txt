cmake_minimum_required(VERSION 3.29)
project(stb)

set(CMAKE_CXX_STANDARD 23)

add_library(stb STATIC
        src/stb_image.cpp
        include/stb/stb_image.h)

target_include_directories(stb PUBLIC include/)