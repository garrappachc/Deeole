include_directories(
  ${CMAKE_SOURCE_DIR}/src/engine
  ${CMAKE_BINARY_DIR}/src/engine
)

add_subdirectory(colors)
add_subdirectory(suzanne)

add_custom_target(demos DEPENDS colors suzanne)