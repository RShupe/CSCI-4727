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
CMAKE_SOURCE_DIR = /tmp/proj3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /tmp/proj3/cmake-build-debug-remote-pi

# Include any dependencies generated for this target.
include CMakeFiles/Proj3.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Proj3.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Proj3.dir/flags.make

CMakeFiles/Proj3.dir/main.cpp.o: CMakeFiles/Proj3.dir/flags.make
CMakeFiles/Proj3.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/tmp/proj3/cmake-build-debug-remote-pi/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Proj3.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Proj3.dir/main.cpp.o -c /tmp/proj3/main.cpp

CMakeFiles/Proj3.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Proj3.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /tmp/proj3/main.cpp > CMakeFiles/Proj3.dir/main.cpp.i

CMakeFiles/Proj3.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Proj3.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /tmp/proj3/main.cpp -o CMakeFiles/Proj3.dir/main.cpp.s

CMakeFiles/Proj3.dir/Address.cpp.o: CMakeFiles/Proj3.dir/flags.make
CMakeFiles/Proj3.dir/Address.cpp.o: ../Address.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/tmp/proj3/cmake-build-debug-remote-pi/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Proj3.dir/Address.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Proj3.dir/Address.cpp.o -c /tmp/proj3/Address.cpp

CMakeFiles/Proj3.dir/Address.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Proj3.dir/Address.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /tmp/proj3/Address.cpp > CMakeFiles/Proj3.dir/Address.cpp.i

CMakeFiles/Proj3.dir/Address.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Proj3.dir/Address.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /tmp/proj3/Address.cpp -o CMakeFiles/Proj3.dir/Address.cpp.s

CMakeFiles/Proj3.dir/L1Cache.cpp.o: CMakeFiles/Proj3.dir/flags.make
CMakeFiles/Proj3.dir/L1Cache.cpp.o: ../L1Cache.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/tmp/proj3/cmake-build-debug-remote-pi/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Proj3.dir/L1Cache.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Proj3.dir/L1Cache.cpp.o -c /tmp/proj3/L1Cache.cpp

CMakeFiles/Proj3.dir/L1Cache.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Proj3.dir/L1Cache.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /tmp/proj3/L1Cache.cpp > CMakeFiles/Proj3.dir/L1Cache.cpp.i

CMakeFiles/Proj3.dir/L1Cache.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Proj3.dir/L1Cache.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /tmp/proj3/L1Cache.cpp -o CMakeFiles/Proj3.dir/L1Cache.cpp.s

CMakeFiles/Proj3.dir/L2Cache.cpp.o: CMakeFiles/Proj3.dir/flags.make
CMakeFiles/Proj3.dir/L2Cache.cpp.o: ../L2Cache.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/tmp/proj3/cmake-build-debug-remote-pi/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/Proj3.dir/L2Cache.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Proj3.dir/L2Cache.cpp.o -c /tmp/proj3/L2Cache.cpp

CMakeFiles/Proj3.dir/L2Cache.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Proj3.dir/L2Cache.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /tmp/proj3/L2Cache.cpp > CMakeFiles/Proj3.dir/L2Cache.cpp.i

CMakeFiles/Proj3.dir/L2Cache.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Proj3.dir/L2Cache.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /tmp/proj3/L2Cache.cpp -o CMakeFiles/Proj3.dir/L2Cache.cpp.s

CMakeFiles/Proj3.dir/TLB.cpp.o: CMakeFiles/Proj3.dir/flags.make
CMakeFiles/Proj3.dir/TLB.cpp.o: ../TLB.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/tmp/proj3/cmake-build-debug-remote-pi/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/Proj3.dir/TLB.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Proj3.dir/TLB.cpp.o -c /tmp/proj3/TLB.cpp

CMakeFiles/Proj3.dir/TLB.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Proj3.dir/TLB.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /tmp/proj3/TLB.cpp > CMakeFiles/Proj3.dir/TLB.cpp.i

CMakeFiles/Proj3.dir/TLB.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Proj3.dir/TLB.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /tmp/proj3/TLB.cpp -o CMakeFiles/Proj3.dir/TLB.cpp.s

CMakeFiles/Proj3.dir/PageTable.cpp.o: CMakeFiles/Proj3.dir/flags.make
CMakeFiles/Proj3.dir/PageTable.cpp.o: ../PageTable.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/tmp/proj3/cmake-build-debug-remote-pi/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/Proj3.dir/PageTable.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Proj3.dir/PageTable.cpp.o -c /tmp/proj3/PageTable.cpp

CMakeFiles/Proj3.dir/PageTable.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Proj3.dir/PageTable.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /tmp/proj3/PageTable.cpp > CMakeFiles/Proj3.dir/PageTable.cpp.i

CMakeFiles/Proj3.dir/PageTable.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Proj3.dir/PageTable.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /tmp/proj3/PageTable.cpp -o CMakeFiles/Proj3.dir/PageTable.cpp.s

# Object files for target Proj3
Proj3_OBJECTS = \
"CMakeFiles/Proj3.dir/main.cpp.o" \
"CMakeFiles/Proj3.dir/Address.cpp.o" \
"CMakeFiles/Proj3.dir/L1Cache.cpp.o" \
"CMakeFiles/Proj3.dir/L2Cache.cpp.o" \
"CMakeFiles/Proj3.dir/TLB.cpp.o" \
"CMakeFiles/Proj3.dir/PageTable.cpp.o"

# External object files for target Proj3
Proj3_EXTERNAL_OBJECTS =

Proj3: CMakeFiles/Proj3.dir/main.cpp.o
Proj3: CMakeFiles/Proj3.dir/Address.cpp.o
Proj3: CMakeFiles/Proj3.dir/L1Cache.cpp.o
Proj3: CMakeFiles/Proj3.dir/L2Cache.cpp.o
Proj3: CMakeFiles/Proj3.dir/TLB.cpp.o
Proj3: CMakeFiles/Proj3.dir/PageTable.cpp.o
Proj3: CMakeFiles/Proj3.dir/build.make
Proj3: CMakeFiles/Proj3.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/tmp/proj3/cmake-build-debug-remote-pi/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable Proj3"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Proj3.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Proj3.dir/build: Proj3

.PHONY : CMakeFiles/Proj3.dir/build

CMakeFiles/Proj3.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Proj3.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Proj3.dir/clean

CMakeFiles/Proj3.dir/depend:
	cd /tmp/proj3/cmake-build-debug-remote-pi && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /tmp/proj3 /tmp/proj3 /tmp/proj3/cmake-build-debug-remote-pi /tmp/proj3/cmake-build-debug-remote-pi /tmp/proj3/cmake-build-debug-remote-pi/CMakeFiles/Proj3.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Proj3.dir/depend
