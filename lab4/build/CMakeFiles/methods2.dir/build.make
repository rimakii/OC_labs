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
CMAKE_SOURCE_DIR = /workspaces/os/lab4

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /workspaces/os/lab4/build

# Include any dependencies generated for this target.
include CMakeFiles/methods2.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/methods2.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/methods2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/methods2.dir/flags.make

CMakeFiles/methods2.dir/lib/libmethods2.c.o: CMakeFiles/methods2.dir/flags.make
CMakeFiles/methods2.dir/lib/libmethods2.c.o: /workspaces/os/lab4/lib/libmethods2.c
CMakeFiles/methods2.dir/lib/libmethods2.c.o: CMakeFiles/methods2.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/workspaces/os/lab4/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/methods2.dir/lib/libmethods2.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/methods2.dir/lib/libmethods2.c.o -MF CMakeFiles/methods2.dir/lib/libmethods2.c.o.d -o CMakeFiles/methods2.dir/lib/libmethods2.c.o -c /workspaces/os/lab4/lib/libmethods2.c

CMakeFiles/methods2.dir/lib/libmethods2.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/methods2.dir/lib/libmethods2.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /workspaces/os/lab4/lib/libmethods2.c > CMakeFiles/methods2.dir/lib/libmethods2.c.i

CMakeFiles/methods2.dir/lib/libmethods2.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/methods2.dir/lib/libmethods2.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /workspaces/os/lab4/lib/libmethods2.c -o CMakeFiles/methods2.dir/lib/libmethods2.c.s

# Object files for target methods2
methods2_OBJECTS = \
"CMakeFiles/methods2.dir/lib/libmethods2.c.o"

# External object files for target methods2
methods2_EXTERNAL_OBJECTS =

libmethods2.so: CMakeFiles/methods2.dir/lib/libmethods2.c.o
libmethods2.so: CMakeFiles/methods2.dir/build.make
libmethods2.so: CMakeFiles/methods2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/workspaces/os/lab4/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C shared library libmethods2.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/methods2.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/methods2.dir/build: libmethods2.so
.PHONY : CMakeFiles/methods2.dir/build

CMakeFiles/methods2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/methods2.dir/cmake_clean.cmake
.PHONY : CMakeFiles/methods2.dir/clean

CMakeFiles/methods2.dir/depend:
	cd /workspaces/os/lab4/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /workspaces/os/lab4 /workspaces/os/lab4 /workspaces/os/lab4/build /workspaces/os/lab4/build /workspaces/os/lab4/build/CMakeFiles/methods2.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/methods2.dir/depend
