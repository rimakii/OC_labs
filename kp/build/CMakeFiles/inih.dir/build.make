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
CMAKE_SOURCE_DIR = /workspaces/os/kp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /workspaces/os/kp/build

# Include any dependencies generated for this target.
include CMakeFiles/inih.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/inih.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/inih.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/inih.dir/flags.make

CMakeFiles/inih.dir/inih/ini.c.o: CMakeFiles/inih.dir/flags.make
CMakeFiles/inih.dir/inih/ini.c.o: /workspaces/os/kp/inih/ini.c
CMakeFiles/inih.dir/inih/ini.c.o: CMakeFiles/inih.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/workspaces/os/kp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/inih.dir/inih/ini.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/inih.dir/inih/ini.c.o -MF CMakeFiles/inih.dir/inih/ini.c.o.d -o CMakeFiles/inih.dir/inih/ini.c.o -c /workspaces/os/kp/inih/ini.c

CMakeFiles/inih.dir/inih/ini.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/inih.dir/inih/ini.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /workspaces/os/kp/inih/ini.c > CMakeFiles/inih.dir/inih/ini.c.i

CMakeFiles/inih.dir/inih/ini.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/inih.dir/inih/ini.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /workspaces/os/kp/inih/ini.c -o CMakeFiles/inih.dir/inih/ini.c.s

CMakeFiles/inih.dir/inih/cpp/INIReader.cpp.o: CMakeFiles/inih.dir/flags.make
CMakeFiles/inih.dir/inih/cpp/INIReader.cpp.o: /workspaces/os/kp/inih/cpp/INIReader.cpp
CMakeFiles/inih.dir/inih/cpp/INIReader.cpp.o: CMakeFiles/inih.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/workspaces/os/kp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/inih.dir/inih/cpp/INIReader.cpp.o"
	/usr/local/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/inih.dir/inih/cpp/INIReader.cpp.o -MF CMakeFiles/inih.dir/inih/cpp/INIReader.cpp.o.d -o CMakeFiles/inih.dir/inih/cpp/INIReader.cpp.o -c /workspaces/os/kp/inih/cpp/INIReader.cpp

CMakeFiles/inih.dir/inih/cpp/INIReader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/inih.dir/inih/cpp/INIReader.cpp.i"
	/usr/local/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /workspaces/os/kp/inih/cpp/INIReader.cpp > CMakeFiles/inih.dir/inih/cpp/INIReader.cpp.i

CMakeFiles/inih.dir/inih/cpp/INIReader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/inih.dir/inih/cpp/INIReader.cpp.s"
	/usr/local/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /workspaces/os/kp/inih/cpp/INIReader.cpp -o CMakeFiles/inih.dir/inih/cpp/INIReader.cpp.s

# Object files for target inih
inih_OBJECTS = \
"CMakeFiles/inih.dir/inih/ini.c.o" \
"CMakeFiles/inih.dir/inih/cpp/INIReader.cpp.o"

# External object files for target inih
inih_EXTERNAL_OBJECTS =

libinih.a: CMakeFiles/inih.dir/inih/ini.c.o
libinih.a: CMakeFiles/inih.dir/inih/cpp/INIReader.cpp.o
libinih.a: CMakeFiles/inih.dir/build.make
libinih.a: CMakeFiles/inih.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/workspaces/os/kp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX static library libinih.a"
	$(CMAKE_COMMAND) -P CMakeFiles/inih.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/inih.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/inih.dir/build: libinih.a
.PHONY : CMakeFiles/inih.dir/build

CMakeFiles/inih.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/inih.dir/cmake_clean.cmake
.PHONY : CMakeFiles/inih.dir/clean

CMakeFiles/inih.dir/depend:
	cd /workspaces/os/kp/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /workspaces/os/kp /workspaces/os/kp /workspaces/os/kp/build /workspaces/os/kp/build /workspaces/os/kp/build/CMakeFiles/inih.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/inih.dir/depend

