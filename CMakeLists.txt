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

install(FILES FindDeeole.cmake DESTINATION ${CMAKE_ROOT}/Modules)

# add a target to generate API documentation with Doxygen
find_package(Doxygen QUIET)
if (DOXYGEN_FOUND)
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
  add_custom_target(doc
    ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Generating API documentation with Doxygen" VERBATIM
  )
endif(DOXYGEN_FOUND)
