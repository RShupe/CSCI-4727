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
CMAKE_SOURCE_DIR = /tmp/tmp.VAXxmHxyTl

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /tmp/tmp.VAXxmHxyTl/cmake-build-debug-remote-pi

# Include any dependencies generated for this target.
include CMakeFiles/Ni.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Ni.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Ni.dir/flags.make

CMakeFiles/Ni.dir/main.cpp.o: CMakeFiles/Ni.dir/flags.make
CMakeFiles/Ni.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/tmp/tmp.VAXxmHxyTl/cmake-build-debug-remote-pi/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Ni.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Ni.dir/main.cpp.o -c /tmp/tmp.VAXxmHxyTl/main.cpp

CMakeFiles/Ni.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Ni.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /tmp/tmp.VAXxmHxyTl/main.cpp > CMakeFiles/Ni.dir/main.cpp.i

CMakeFiles/Ni.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Ni.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /tmp/tmp.VAXxmHxyTl/main.cpp -o CMakeFiles/Ni.dir/main.cpp.s

CMakeFiles/Ni.dir/Logger.cpp.o: CMakeFiles/Ni.dir/flags.make
CMakeFiles/Ni.dir/Logger.cpp.o: ../Logger.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/tmp/tmp.VAXxmHxyTl/cmake-build-debug-remote-pi/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Ni.dir/Logger.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Ni.dir/Logger.cpp.o -c /tmp/tmp.VAXxmHxyTl/Logger.cpp

CMakeFiles/Ni.dir/Logger.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Ni.dir/Logger.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /tmp/tmp.VAXxmHxyTl/Logger.cpp > CMakeFiles/Ni.dir/Logger.cpp.i

CMakeFiles/Ni.dir/Logger.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Ni.dir/Logger.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /tmp/tmp.VAXxmHxyTl/Logger.cpp -o CMakeFiles/Ni.dir/Logger.cpp.s

# Object files for target Ni
Ni_OBJECTS = \
"CMakeFiles/Ni.dir/main.cpp.o" \
"CMakeFiles/Ni.dir/Logger.cpp.o"

# External object files for target Ni
Ni_EXTERNAL_OBJECTS =

Ni: CMakeFiles/Ni.dir/main.cpp.o
Ni: CMakeFiles/Ni.dir/Logger.cpp.o
Ni: CMakeFiles/Ni.dir/build.make
Ni: CMakeFiles/Ni.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/tmp/tmp.VAXxmHxyTl/cmake-build-debug-remote-pi/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable Ni"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Ni.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Ni.dir/build: Ni

.PHONY : CMakeFiles/Ni.dir/build

CMakeFiles/Ni.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Ni.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Ni.dir/clean

CMakeFiles/Ni.dir/depend:
	cd /tmp/tmp.VAXxmHxyTl/cmake-build-debug-remote-pi && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /tmp/tmp.VAXxmHxyTl /tmp/tmp.VAXxmHxyTl /tmp/tmp.VAXxmHxyTl/cmake-build-debug-remote-pi /tmp/tmp.VAXxmHxyTl/cmake-build-debug-remote-pi /tmp/tmp.VAXxmHxyTl/cmake-build-debug-remote-pi/CMakeFiles/Ni.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Ni.dir/depend

