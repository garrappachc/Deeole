# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/garapich/Dokumenty/Deeole

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/garapich/Dokumenty/Deeole/build

# Include any dependencies generated for this target.
include src/engine/CMakeFiles/deeole.dir/depend.make

# Include the progress variables for this target.
include src/engine/CMakeFiles/deeole.dir/progress.make

# Include the compile flags for this target's objects.
include src/engine/CMakeFiles/deeole.dir/flags.make

src/engine/CMakeFiles/deeole.dir/main.cpp.o: src/engine/CMakeFiles/deeole.dir/flags.make
src/engine/CMakeFiles/deeole.dir/main.cpp.o: src/engine/main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/garapich/Dokumenty/Deeole/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/engine/CMakeFiles/deeole.dir/main.cpp.o"
	cd /home/garapich/Dokumenty/Deeole/build/src/engine && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/deeole.dir/main.cpp.o -c /home/garapich/Dokumenty/Deeole/build/src/engine/main.cpp

src/engine/CMakeFiles/deeole.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/deeole.dir/main.cpp.i"
	cd /home/garapich/Dokumenty/Deeole/build/src/engine && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/garapich/Dokumenty/Deeole/build/src/engine/main.cpp > CMakeFiles/deeole.dir/main.cpp.i

src/engine/CMakeFiles/deeole.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/deeole.dir/main.cpp.s"
	cd /home/garapich/Dokumenty/Deeole/build/src/engine && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/garapich/Dokumenty/Deeole/build/src/engine/main.cpp -o CMakeFiles/deeole.dir/main.cpp.s

src/engine/CMakeFiles/deeole.dir/main.cpp.o.requires:
.PHONY : src/engine/CMakeFiles/deeole.dir/main.cpp.o.requires

src/engine/CMakeFiles/deeole.dir/main.cpp.o.provides: src/engine/CMakeFiles/deeole.dir/main.cpp.o.requires
	$(MAKE) -f src/engine/CMakeFiles/deeole.dir/build.make src/engine/CMakeFiles/deeole.dir/main.cpp.o.provides.build
.PHONY : src/engine/CMakeFiles/deeole.dir/main.cpp.o.provides

src/engine/CMakeFiles/deeole.dir/main.cpp.o.provides.build: src/engine/CMakeFiles/deeole.dir/main.cpp.o

# Object files for target deeole
deeole_OBJECTS = \
"CMakeFiles/deeole.dir/main.cpp.o"

# External object files for target deeole
deeole_EXTERNAL_OBJECTS =

libdeeole.so.1.0.0: src/engine/CMakeFiles/deeole.dir/main.cpp.o
libdeeole.so.1.0.0: src/engine/CMakeFiles/deeole.dir/build.make
libdeeole.so.1.0.0: src/engine/core/libcore.a
libdeeole.so.1.0.0: /usr/lib64/libGLU.so
libdeeole.so.1.0.0: /usr/lib64/libGL.so
libdeeole.so.1.0.0: /usr/lib64/libSM.so
libdeeole.so.1.0.0: /usr/lib64/libICE.so
libdeeole.so.1.0.0: /usr/lib64/libX11.so
libdeeole.so.1.0.0: /usr/lib64/libXext.so
libdeeole.so.1.0.0: /usr/lib64/libSM.so
libdeeole.so.1.0.0: /usr/lib64/libICE.so
libdeeole.so.1.0.0: /usr/lib64/libX11.so
libdeeole.so.1.0.0: /usr/lib64/libXext.so
libdeeole.so.1.0.0: src/engine/CMakeFiles/deeole.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX shared library ../../libdeeole.so"
	cd /home/garapich/Dokumenty/Deeole/build/src/engine && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/deeole.dir/link.txt --verbose=$(VERBOSE)
	cd /home/garapich/Dokumenty/Deeole/build/src/engine && $(CMAKE_COMMAND) -E cmake_symlink_library ../../libdeeole.so.1.0.0 ../../libdeeole.so.1 ../../libdeeole.so

libdeeole.so.1: libdeeole.so.1.0.0

libdeeole.so: libdeeole.so.1.0.0

# Rule to build all files generated by this target.
src/engine/CMakeFiles/deeole.dir/build: libdeeole.so
.PHONY : src/engine/CMakeFiles/deeole.dir/build

src/engine/CMakeFiles/deeole.dir/requires: src/engine/CMakeFiles/deeole.dir/main.cpp.o.requires
.PHONY : src/engine/CMakeFiles/deeole.dir/requires

src/engine/CMakeFiles/deeole.dir/clean:
	cd /home/garapich/Dokumenty/Deeole/build/src/engine && $(CMAKE_COMMAND) -P CMakeFiles/deeole.dir/cmake_clean.cmake
.PHONY : src/engine/CMakeFiles/deeole.dir/clean

src/engine/CMakeFiles/deeole.dir/depend:
	cd /home/garapich/Dokumenty/Deeole/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/garapich/Dokumenty/Deeole /home/garapich/Dokumenty/Deeole/src/engine /home/garapich/Dokumenty/Deeole/build /home/garapich/Dokumenty/Deeole/build/src/engine /home/garapich/Dokumenty/Deeole/build/src/engine/CMakeFiles/deeole.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/engine/CMakeFiles/deeole.dir/depend

