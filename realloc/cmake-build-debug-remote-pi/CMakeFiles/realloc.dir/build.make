# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /tmp/tmp.p8V6148oEn

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /tmp/tmp.p8V6148oEn/cmake-build-debug-remote-pi

# Include any dependencies generated for this target.
include CMakeFiles/realloc.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/realloc.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/realloc.dir/flags.make

CMakeFiles/realloc.dir/main.cpp.o: CMakeFiles/realloc.dir/flags.make
CMakeFiles/realloc.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/tmp/tmp.p8V6148oEn/cmake-build-debug-remote-pi/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/realloc.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/realloc.dir/main.cpp.o -c /tmp/tmp.p8V6148oEn/main.cpp

CMakeFiles/realloc.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/realloc.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /tmp/tmp.p8V6148oEn/main.cpp > CMakeFiles/realloc.dir/main.cpp.i

CMakeFiles/realloc.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/realloc.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /tmp/tmp.p8V6148oEn/main.cpp -o CMakeFiles/realloc.dir/main.cpp.s

# Object files for target realloc
realloc_OBJECTS = \
"CMakeFiles/realloc.dir/main.cpp.o"

# External object files for target realloc
realloc_EXTERNAL_OBJECTS =

realloc: CMakeFiles/realloc.dir/main.cpp.o
realloc: CMakeFiles/realloc.dir/build.make
realloc: CMakeFiles/realloc.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/tmp/tmp.p8V6148oEn/cmake-build-debug-remote-pi/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable realloc"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/realloc.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/realloc.dir/build: realloc

.PHONY : CMakeFiles/realloc.dir/build

CMakeFiles/realloc.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/realloc.dir/cmake_clean.cmake
.PHONY : CMakeFiles/realloc.dir/clean

CMakeFiles/realloc.dir/depend:
	cd /tmp/tmp.p8V6148oEn/cmake-build-debug-remote-pi && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /tmp/tmp.p8V6148oEn /tmp/tmp.p8V6148oEn /tmp/tmp.p8V6148oEn/cmake-build-debug-remote-pi /tmp/tmp.p8V6148oEn/cmake-build-debug-remote-pi /tmp/tmp.p8V6148oEn/cmake-build-debug-remote-pi/CMakeFiles/realloc.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/realloc.dir/depend

