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
CMAKE_SOURCE_DIR = /tmp/tmp.rzCoWRqYNu

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /tmp/tmp.rzCoWRqYNu/cmake-build-debug-remote-pi

# Include any dependencies generated for this target.
include CMakeFiles/Lab3.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Lab3.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Lab3.dir/flags.make

CMakeFiles/Lab3.dir/main.cpp.o: CMakeFiles/Lab3.dir/flags.make
CMakeFiles/Lab3.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/tmp/tmp.rzCoWRqYNu/cmake-build-debug-remote-pi/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Lab3.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Lab3.dir/main.cpp.o -c /tmp/tmp.rzCoWRqYNu/main.cpp

CMakeFiles/Lab3.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Lab3.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /tmp/tmp.rzCoWRqYNu/main.cpp > CMakeFiles/Lab3.dir/main.cpp.i

CMakeFiles/Lab3.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Lab3.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /tmp/tmp.rzCoWRqYNu/main.cpp -o CMakeFiles/Lab3.dir/main.cpp.s

# Object files for target Lab3
Lab3_OBJECTS = \
"CMakeFiles/Lab3.dir/main.cpp.o"

# External object files for target Lab3
Lab3_EXTERNAL_OBJECTS =

Lab3: CMakeFiles/Lab3.dir/main.cpp.o
Lab3: CMakeFiles/Lab3.dir/build.make
Lab3: CMakeFiles/Lab3.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/tmp/tmp.rzCoWRqYNu/cmake-build-debug-remote-pi/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Lab3"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Lab3.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Lab3.dir/build: Lab3

.PHONY : CMakeFiles/Lab3.dir/build

CMakeFiles/Lab3.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Lab3.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Lab3.dir/clean

CMakeFiles/Lab3.dir/depend:
	cd /tmp/tmp.rzCoWRqYNu/cmake-build-debug-remote-pi && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /tmp/tmp.rzCoWRqYNu /tmp/tmp.rzCoWRqYNu /tmp/tmp.rzCoWRqYNu/cmake-build-debug-remote-pi /tmp/tmp.rzCoWRqYNu/cmake-build-debug-remote-pi /tmp/tmp.rzCoWRqYNu/cmake-build-debug-remote-pi/CMakeFiles/Lab3.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Lab3.dir/depend
