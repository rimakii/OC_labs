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
CMAKE_SOURCE_DIR = /workspaces/os/lab1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /workspaces/os/lab1/build

# Include any dependencies generated for this target.
include CMakeFiles/CreateProcess.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/CreateProcess.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/CreateProcess.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/CreateProcess.dir/flags.make

CMakeFiles/CreateProcess.dir/src/CreateProcess.c.o: CMakeFiles/CreateProcess.dir/flags.make
CMakeFiles/CreateProcess.dir/src/CreateProcess.c.o: /workspaces/os/lab1/src/CreateProcess.c
CMakeFiles/CreateProcess.dir/src/CreateProcess.c.o: CMakeFiles/CreateProcess.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/workspaces/os/lab1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/CreateProcess.dir/src/CreateProcess.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/CreateProcess.dir/src/CreateProcess.c.o -MF CMakeFiles/CreateProcess.dir/src/CreateProcess.c.o.d -o CMakeFiles/CreateProcess.dir/src/CreateProcess.c.o -c /workspaces/os/lab1/src/CreateProcess.c

CMakeFiles/CreateProcess.dir/src/CreateProcess.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/CreateProcess.dir/src/CreateProcess.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /workspaces/os/lab1/src/CreateProcess.c > CMakeFiles/CreateProcess.dir/src/CreateProcess.c.i

CMakeFiles/CreateProcess.dir/src/CreateProcess.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/CreateProcess.dir/src/CreateProcess.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /workspaces/os/lab1/src/CreateProcess.c -o CMakeFiles/CreateProcess.dir/src/CreateProcess.c.s

# Object files for target CreateProcess
CreateProcess_OBJECTS = \
"CMakeFiles/CreateProcess.dir/src/CreateProcess.c.o"

# External object files for target CreateProcess
CreateProcess_EXTERNAL_OBJECTS =

CreateProcess: CMakeFiles/CreateProcess.dir/src/CreateProcess.c.o
CreateProcess: CMakeFiles/CreateProcess.dir/build.make
CreateProcess: CMakeFiles/CreateProcess.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/workspaces/os/lab1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable CreateProcess"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/CreateProcess.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/CreateProcess.dir/build: CreateProcess
.PHONY : CMakeFiles/CreateProcess.dir/build

CMakeFiles/CreateProcess.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/CreateProcess.dir/cmake_clean.cmake
.PHONY : CMakeFiles/CreateProcess.dir/clean

CMakeFiles/CreateProcess.dir/depend:
	cd /workspaces/os/lab1/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /workspaces/os/lab1 /workspaces/os/lab1 /workspaces/os/lab1/build /workspaces/os/lab1/build /workspaces/os/lab1/build/CMakeFiles/CreateProcess.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/CreateProcess.dir/depend

