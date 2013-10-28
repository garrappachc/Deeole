# Try to find Deeole
#
# DEEOLE_FOUND - System has Deeole
# DEEOLE_LIBRARIES - The libraries needed to use Deeole

find_package(PkgConfig)
pkg_check_modules(PC_DEEOLE deeole)

find_library(DEEOLE_LIBRARY NAMES deeole
  HINTS ${PC_DEEOLE_LIBDIR} ${PC_DEEOLE_LIBRARY_DIRS})

find_path(DEEOLE_INCLUDE_DIR core/deeglobal.h
  HINTS ${PC_DEEOLE_INCLUDEDIR} ${PC_DEEOLE_INCLUDE_DIRS}
  PATH_SUFFIXES deeole)

set(DEEOLE_LIBRARIES ${DEEOLE_LIBRARY})
set(DEEOLE_INCLUDE_DIRS ${DEEOLE_INCLUDE_DIR})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Deeole DEFAULT_MSG DEEOLE_LIBRARY DEEOLE_INCLUDE_DIR)

mark_as_advanced(DEEOLE_INCLUDE_DIR DEEOLE_LIBRARY)
