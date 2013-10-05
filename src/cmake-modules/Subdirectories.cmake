macro(deeole_subdirectory_start SUBDIR)
  set(deeole_${SUBDIR}_SOURCES "")
endmacro(deeole_subdirectory_start)

macro(deeole_subdirectory_sources SUBDIR SRCS)
  if (NOT "${SRCS}" STREQUAL "")
    set(deeole_${SUBDIR}_SOURCES
      ${deeole_${SUBDIR}_SOURCES} ${SRCS}
    )
  endif (NOT "${SRCS}" STREQUAL "")
endmacro(deeole_subdirectory_sources SUBDIR SRCS)

macro(deeole_subdirectory_end SUBDIR)
  if (NOT "${deeole_${SUBDIR}_SOURCES}" STREQUAL "")
    add_library(${SUBDIR} STATIC
      ${deeole_${SUBDIR}_SOURCES}
    )
  endif (NOT "${deeole_${SUBDIR}_SOURCES}" STREQUAL "")
endmacro(deeole_subdirectory_end)
