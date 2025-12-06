# Install script for directory: C:/Users/alikg/CLionProjects/NeonEngine/neonEngine/dependencies/miniaudio

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/sandboxApp")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "C:/msys64/mingw64/bin/objdump.exe")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/miniaudio" TYPE FILE FILES "C:/Users/alikg/CLionProjects/NeonEngine/neonEngine/dependencies/miniaudio/miniaudio.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/miniaudio/extras/nodes/ma_channel_combiner_node" TYPE FILE FILES "C:/Users/alikg/CLionProjects/NeonEngine/neonEngine/dependencies/miniaudio/extras/nodes/ma_channel_combiner_node/ma_channel_combiner_node.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/miniaudio/extras/nodes/ma_channel_separator_node" TYPE FILE FILES "C:/Users/alikg/CLionProjects/NeonEngine/neonEngine/dependencies/miniaudio/extras/nodes/ma_channel_separator_node/ma_channel_separator_node.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/miniaudio/extras/nodes/ma_ltrim_node" TYPE FILE FILES "C:/Users/alikg/CLionProjects/NeonEngine/neonEngine/dependencies/miniaudio/extras/nodes/ma_ltrim_node/ma_ltrim_node.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/miniaudio/extras/nodes/ma_reverb_node" TYPE FILE FILES "C:/Users/alikg/CLionProjects/NeonEngine/neonEngine/dependencies/miniaudio/extras/nodes/ma_reverb_node/ma_reverb_node.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/miniaudio/extras/nodes/ma_vocoder_node" TYPE FILE FILES "C:/Users/alikg/CLionProjects/NeonEngine/neonEngine/dependencies/miniaudio/extras/nodes/ma_vocoder_node/ma_vocoder_node.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/alikg/CLionProjects/NeonEngine/sandboxApp/cmake-build-release/neonEngine/dependencies/miniaudio/miniaudio.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/alikg/CLionProjects/NeonEngine/sandboxApp/cmake-build-release/neonEngine/dependencies/miniaudio/libminiaudio.a")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/alikg/CLionProjects/NeonEngine/sandboxApp/cmake-build-release/neonEngine/dependencies/miniaudio/libminiaudio_channel_combiner_node.a")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/alikg/CLionProjects/NeonEngine/sandboxApp/cmake-build-release/neonEngine/dependencies/miniaudio/libminiaudio_channel_separator_node.a")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/alikg/CLionProjects/NeonEngine/sandboxApp/cmake-build-release/neonEngine/dependencies/miniaudio/libminiaudio_ltrim_node.a")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/alikg/CLionProjects/NeonEngine/sandboxApp/cmake-build-release/neonEngine/dependencies/miniaudio/libminiaudio_reverb_node.a")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/alikg/CLionProjects/NeonEngine/sandboxApp/cmake-build-release/neonEngine/dependencies/miniaudio/libminiaudio_vocoder_node.a")
endif()

