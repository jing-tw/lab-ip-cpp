# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_SOURCE_DIR = /home/jing/test/example

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jing/test/example

# Include any dependencies generated for this target.
include CMakeFiles/OpenGLDemo.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/OpenGLDemo.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/OpenGLDemo.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/OpenGLDemo.dir/flags.make

CMakeFiles/OpenGLDemo.dir/src/main.cpp.o: CMakeFiles/OpenGLDemo.dir/flags.make
CMakeFiles/OpenGLDemo.dir/src/main.cpp.o: src/main.cpp
CMakeFiles/OpenGLDemo.dir/src/main.cpp.o: CMakeFiles/OpenGLDemo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jing/test/example/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/OpenGLDemo.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/OpenGLDemo.dir/src/main.cpp.o -MF CMakeFiles/OpenGLDemo.dir/src/main.cpp.o.d -o CMakeFiles/OpenGLDemo.dir/src/main.cpp.o -c /home/jing/test/example/src/main.cpp

CMakeFiles/OpenGLDemo.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/OpenGLDemo.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jing/test/example/src/main.cpp > CMakeFiles/OpenGLDemo.dir/src/main.cpp.i

CMakeFiles/OpenGLDemo.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/OpenGLDemo.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jing/test/example/src/main.cpp -o CMakeFiles/OpenGLDemo.dir/src/main.cpp.s

# Object files for target OpenGLDemo
OpenGLDemo_OBJECTS = \
"CMakeFiles/OpenGLDemo.dir/src/main.cpp.o"

# External object files for target OpenGLDemo
OpenGLDemo_EXTERNAL_OBJECTS =

OpenGLDemo: CMakeFiles/OpenGLDemo.dir/src/main.cpp.o
OpenGLDemo: CMakeFiles/OpenGLDemo.dir/build.make
OpenGLDemo: /usr/lib/x86_64-linux-gnu/libGL.so
OpenGLDemo: /usr/lib/x86_64-linux-gnu/libGLU.so
OpenGLDemo: /usr/lib/x86_64-linux-gnu/libglfw.so.3.3
OpenGLDemo: libglad.a
OpenGLDemo: CMakeFiles/OpenGLDemo.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jing/test/example/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable OpenGLDemo"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/OpenGLDemo.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/OpenGLDemo.dir/build: OpenGLDemo
.PHONY : CMakeFiles/OpenGLDemo.dir/build

CMakeFiles/OpenGLDemo.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/OpenGLDemo.dir/cmake_clean.cmake
.PHONY : CMakeFiles/OpenGLDemo.dir/clean

CMakeFiles/OpenGLDemo.dir/depend:
	cd /home/jing/test/example && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jing/test/example /home/jing/test/example /home/jing/test/example /home/jing/test/example /home/jing/test/example/CMakeFiles/OpenGLDemo.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/OpenGLDemo.dir/depend

