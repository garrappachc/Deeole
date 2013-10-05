project(deeole)
cmake_minimum_required(VERSION 2.8)

find_package(OpenGL REQUIRED)

if (UNIX AND NOT APPLE)
  set(LINUX 1)
endif (UNIX AND NOT APPLE)

if (LINUX)
  find_package(X11 REQUIRED)
endif (LINUX)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

# flags for gcc
if (CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "-std=c++11 -fvisibility=hidden")
  set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -DDEE_DEBUG")
  
  set(CMAKE_SHARED_LINKER_FLAGS "-Wl,--no-undefined")
endif (CMAKE_COMPILER_IS_GNUCXX)

add_subdirectory(src)
