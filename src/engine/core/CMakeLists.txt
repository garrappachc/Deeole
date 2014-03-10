deeole_subdirectory_start(core)

set (core_SRCS
  application.cpp
  camera.cpp
  color.cpp
  cursor.cpp
  deeglobal.cpp
  freecamera.cpp
  glbridge.cpp
  inputhandler.cpp
  item.cpp
  keyboard.cpp
  mesh.cpp
  modelviewmatrix.cpp
  mouse.cpp
  mutex.cpp
  object.cpp
  projectionmatrix.cpp
  renderable.cpp
  scene.cpp
  scenemanager.cpp
  scopedmutex.cpp
  size.cpp
  slotqueue.cpp
  thread.cpp
  timer.cpp
  transformationmatrix.cpp
  userinterface.cpp
  vertex.cpp
  window.cpp
)
if (LINUX)
  set (core_SRCS ${core_SRCS}
    x11/x11bridge.cpp
    x11/x11cursor.cpp
    x11/x11userinterface.cpp
    x11/x11window.cpp
  )
endif (LINUX)
deeole_subdirectory_sources(core "${core_SRCS}")

set (core_HEADERS
  application.h
  deeglobal.h
  mutex.h
  object.h
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
