set(deeole_TARGET deeole)
include(Subdirectories)

if (CMAKE_COMPILER_IS_GNUCXX)
  add_definitions("-fPIC")
endif (CMAKE_COMPILER_IS_GNUCXX)

file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/main.cpp "")
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.h.in
  ${CMAKE_CURRENT_BINARY_DIR}/config.h)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_library(${deeole_TARGET} SHARED "${CMAKE_CURRENT_BINARY_DIR}/main.cpp")
set_target_properties(${deeole_TARGET} PROPERTIES VERSION 1.0.0 SOVERSION 1)

set(deeole_SUBDIRS
  core
)

foreach(DIR ${deeole_SUBDIRS})
  add_subdirectory(${DIR})
  add_dependencies(${deeole_TARGET} ${DIR})
endforeach(DIR)

target_link_libraries(${deeole_TARGET}
  -Wl,--start-group
  -Wl,--whole-archive
  ${deeole_SUBDIRS}
  -Wl,--no-whole-archive
  -Wl,--end-group
)

target_link_libraries(${deeole_TARGET}
  ${OPENGL_LIBRARIES})

if (LINUX)
  target_link_libraries(${deeole_TARGET}
    pthread
    ${X11_LIBRARIES}
  )
endif (LINUX)

install(TARGETS ${deeole_TARGET}
  LIBRARY DESTINATION lib)
