macro(deeole_subdirectory_start SUBDIR)
  set(deeole_${SUBDIR}_SOURCES "")
  set(deeole_${SUBDIR}_HEADERS "")
endmacro(deeole_subdirectory_start)

macro(deeole_subdirectory_sources SUBDIR SRCS)
  if (NOT "${SRCS}" STREQUAL "")
    set(deeole_${SUBDIR}_SOURCES
      ${deeole_${SUBDIR}_SOURCES} ${SRCS}
    )
  endif (NOT "${SRCS}" STREQUAL "")
endmacro(deeole_subdirectory_sources)

macro(deeole_subdirectory_headers SUBDIR HEADERS)
  if (NOT "${HEADERS}" STREQUAL "")
    set(deeole_${SUBDIR}_HEADERS
      ${deeole_${SUBDIR}_HEADERS} ${HEADERS}
    )
  endif (NOT "${HEADERS}" STREQUAL "")
endmacro(deeole_subdirectory_headers)

macro(deeole_subdirectory_end SUBDIR)
  if (NOT "${deeole_${SUBDIR}_SOURCES}" STREQUAL "")
    add_library(${SUBDIR} STATIC
      ${deeole_${SUBDIR}_SOURCES}
    )
  endif (NOT "${deeole_${SUBDIR}_SOURCES}" STREQUAL "")
  
  if (NOT "${deeole_${SUBDIR}_HEADERS}" STREQUAL "")
    install(FILES ${deeole_${SUBDIR}_HEADERS}
      DESTINATION include/deeole/${SUBDIR}
    )
  endif (NOT "${deeole_${SUBDIR}_HEADERS}" STREQUAL "")
endmacro(deeole_subdirectory_end)
