deeole_subdirectory_start(items)

set (items_SRCS
  cubeitem.cpp
  pointitem.cpp
  quaditem.cpp
  trianglefanitem.cpp
  triangleitem.cpp
  trianglestripitem.cpp
)
deeole_subdirectory_sources(items "${items_SRCS}")

deeole_subdirectory_end(items)
