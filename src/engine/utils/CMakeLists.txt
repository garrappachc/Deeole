deeole_subdirectory_start(utils)

set (utils_SRCS
  logger.cpp
  output.cpp
)
deeole_subdirectory_sources(utils "${utils_SRCS}")

set (utils_HEADERS
  logger.h
  output.h
)
deeole_subdirectory_headers(utils "${utils_HEADERS}")

deeole_subdirectory_end(utils)
