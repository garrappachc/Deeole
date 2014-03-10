deeole_subdirectory_start(events)

set (events_SRCS
  event.cpp
  namechangeevent.cpp
  visibilitychangeevent.cpp
)
deeole_subdirectory_sources(events "${events_SRCS}")

deeole_subdirectory_end(events)
