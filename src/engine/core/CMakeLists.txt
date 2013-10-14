deeole_subdirectory_start(core)

set (core_SRCS
  application.cpp
  deeglobal.cpp
  eventful.cpp
  mutex.cpp
  scopedmutex.cpp
  slotqueue.cpp
  thread.cpp
  timer.cpp
)
deeole_subdirectory_sources(core "${core_SRCS}")

set (core_HEADERS
  application.h
  deeglobal.h
  eventful.h
  mutex.h
  scopedmutex.h
  signal.h
  singleton.h
  slot.h
  slotqueue.h
  thread.h
  timer.h
)

deeole_subdirectory_headers(core "${core_HEADERS}")

deeole_subdirectory_end(core)
