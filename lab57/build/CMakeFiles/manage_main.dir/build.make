# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /workspaces/os/lab57

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /workspaces/os/lab57/build

# Include any dependencies generated for this target.
include CMakeFiles/manage_main.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/manage_main.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/manage_main.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/manage_main.dir/flags.make

CMakeFiles/manage_main.dir/src/manage_main.cpp.o: CMakeFiles/manage_main.dir/flags.make
CMakeFiles/manage_main.dir/src/manage_main.cpp.o: /workspaces/os/lab57/src/manage_main.cpp
CMakeFiles/manage_main.dir/src/manage_main.cpp.o: CMakeFiles/manage_main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/workspaces/os/lab57/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/manage_main.dir/src/manage_main.cpp.o"
	/usr/local/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/manage_main.dir/src/manage_main.cpp.o -MF CMakeFiles/manage_main.dir/src/manage_main.cpp.o.d -o CMakeFiles/manage_main.dir/src/manage_main.cpp.o -c /workspaces/os/lab57/src/manage_main.cpp

CMakeFiles/manage_main.dir/src/manage_main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/manage_main.dir/src/manage_main.cpp.i"
	/usr/local/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /workspaces/os/lab57/src/manage_main.cpp > CMakeFiles/manage_main.dir/src/manage_main.cpp.i

CMakeFiles/manage_main.dir/src/manage_main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/manage_main.dir/src/manage_main.cpp.s"
	/usr/local/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /workspaces/os/lab57/src/manage_main.cpp -o CMakeFiles/manage_main.dir/src/manage_main.cpp.s

CMakeFiles/manage_main.dir/src/manage_node.cpp.o: CMakeFiles/manage_main.dir/flags.make
CMakeFiles/manage_main.dir/src/manage_node.cpp.o: /workspaces/os/lab57/src/manage_node.cpp
CMakeFiles/manage_main.dir/src/manage_node.cpp.o: CMakeFiles/manage_main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/workspaces/os/lab57/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/manage_main.dir/src/manage_node.cpp.o"
	/usr/local/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/manage_main.dir/src/manage_node.cpp.o -MF CMakeFiles/manage_main.dir/src/manage_node.cpp.o.d -o CMakeFiles/manage_main.dir/src/manage_node.cpp.o -c /workspaces/os/lab57/src/manage_node.cpp

CMakeFiles/manage_main.dir/src/manage_node.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/manage_main.dir/src/manage_node.cpp.i"
	/usr/local/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /workspaces/os/lab57/src/manage_node.cpp > CMakeFiles/manage_main.dir/src/manage_node.cpp.i

CMakeFiles/manage_main.dir/src/manage_node.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/manage_main.dir/src/manage_node.cpp.s"
	/usr/local/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /workspaces/os/lab57/src/manage_node.cpp -o CMakeFiles/manage_main.dir/src/manage_node.cpp.s

# Object files for target manage_main
manage_main_OBJECTS = \
"CMakeFiles/manage_main.dir/src/manage_main.cpp.o" \
"CMakeFiles/manage_main.dir/src/manage_node.cpp.o"

# External object files for target manage_main
manage_main_EXTERNAL_OBJECTS =

manage_main: CMakeFiles/manage_main.dir/src/manage_main.cpp.o
manage_main: CMakeFiles/manage_main.dir/src/manage_node.cpp.o
manage_main: CMakeFiles/manage_main.dir/build.make
manage_main: CMakeFiles/manage_main.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/workspaces/os/lab57/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable manage_main"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/manage_main.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/manage_main.dir/build: manage_main
.PHONY : CMakeFiles/manage_main.dir/build

CMakeFiles/manage_main.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/manage_main.dir/cmake_clean.cmake
.PHONY : CMakeFiles/manage_main.dir/clean

CMakeFiles/manage_main.dir/depend:
	cd /workspaces/os/lab57/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /workspaces/os/lab57 /workspaces/os/lab57 /workspaces/os/lab57/build /workspaces/os/lab57/build /workspaces/os/lab57/build/CMakeFiles/manage_main.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/manage_main.dir/depend
