# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

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
CMAKE_COMMAND = /home/monter/Documents/clion-2019.1.2/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/monter/Documents/clion-2019.1.2/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/monter/Documents/Vecl

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/monter/Documents/Vecl/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Vecl.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Vecl.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Vecl.dir/flags.make

CMakeFiles/Vecl.dir/main.cpp.o: CMakeFiles/Vecl.dir/flags.make
CMakeFiles/Vecl.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/monter/Documents/Vecl/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Vecl.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Vecl.dir/main.cpp.o -c /home/monter/Documents/Vecl/main.cpp

CMakeFiles/Vecl.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Vecl.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/monter/Documents/Vecl/main.cpp > CMakeFiles/Vecl.dir/main.cpp.i

CMakeFiles/Vecl.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Vecl.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/monter/Documents/Vecl/main.cpp -o CMakeFiles/Vecl.dir/main.cpp.s

# Object files for target Vecl
Vecl_OBJECTS = \
"CMakeFiles/Vecl.dir/main.cpp.o"

# External object files for target Vecl
Vecl_EXTERNAL_OBJECTS =

Vecl: CMakeFiles/Vecl.dir/main.cpp.o
Vecl: CMakeFiles/Vecl.dir/build.make
Vecl: /usr/lib/x86_64-linux-gnu/libglfw.so
Vecl: /usr/lib/x86_64-linux-gnu/libvulkan.so
Vecl: CMakeFiles/Vecl.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/monter/Documents/Vecl/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Vecl"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Vecl.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Vecl.dir/build: Vecl

.PHONY : CMakeFiles/Vecl.dir/build

CMakeFiles/Vecl.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Vecl.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Vecl.dir/clean

CMakeFiles/Vecl.dir/depend:
	cd /home/monter/Documents/Vecl/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/monter/Documents/Vecl /home/monter/Documents/Vecl /home/monter/Documents/Vecl/cmake-build-debug /home/monter/Documents/Vecl/cmake-build-debug /home/monter/Documents/Vecl/cmake-build-debug/CMakeFiles/Vecl.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Vecl.dir/depend

