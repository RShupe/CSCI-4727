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
CMAKE_SOURCE_DIR = /tmp/tmp.Rjk4KsvrQr

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /tmp/tmp.Rjk4KsvrQr/cmake-build-debug-remote-pi

# Include any dependencies generated for this target.
include CMakeFiles/untitled.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/untitled.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/untitled.dir/flags.make

CMakeFiles/untitled.dir/main.cpp.o: CMakeFiles/untitled.dir/flags.make
CMakeFiles/untitled.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/tmp/tmp.Rjk4KsvrQr/cmake-build-debug-remote-pi/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/untitled.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/untitled.dir/main.cpp.o -c /tmp/tmp.Rjk4KsvrQr/main.cpp

CMakeFiles/untitled.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/untitled.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /tmp/tmp.Rjk4KsvrQr/main.cpp > CMakeFiles/untitled.dir/main.cpp.i

CMakeFiles/untitled.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/untitled.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /tmp/tmp.Rjk4KsvrQr/main.cpp -o CMakeFiles/untitled.dir/main.cpp.s

# Object files for target untitled
untitled_OBJECTS = \
"CMakeFiles/untitled.dir/main.cpp.o"

# External object files for target untitled
untitled_EXTERNAL_OBJECTS =

untitled: CMakeFiles/untitled.dir/main.cpp.o
untitled: CMakeFiles/untitled.dir/build.make
untitled: CMakeFiles/untitled.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/tmp/tmp.Rjk4KsvrQr/cmake-build-debug-remote-pi/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable untitled"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/untitled.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/untitled.dir/build: untitled

.PHONY : CMakeFiles/untitled.dir/build

CMakeFiles/untitled.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/untitled.dir/cmake_clean.cmake
.PHONY : CMakeFiles/untitled.dir/clean

CMakeFiles/untitled.dir/depend:
	cd /tmp/tmp.Rjk4KsvrQr/cmake-build-debug-remote-pi && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /tmp/tmp.Rjk4KsvrQr /tmp/tmp.Rjk4KsvrQr /tmp/tmp.Rjk4KsvrQr/cmake-build-debug-remote-pi /tmp/tmp.Rjk4KsvrQr/cmake-build-debug-remote-pi /tmp/tmp.Rjk4KsvrQr/cmake-build-debug-remote-pi/CMakeFiles/untitled.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/untitled.dir/depend

