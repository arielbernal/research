# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_SOURCE_DIR = /home/ajbernal/dev/bat/research/gtest-1.7.0

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ajbernal/dev/bat/research/gtest-1.7.0/build

# Include any dependencies generated for this target.
include CMakeFiles/sample6_unittest.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/sample6_unittest.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/sample6_unittest.dir/flags.make

CMakeFiles/sample6_unittest.dir/samples/sample6_unittest.cc.o: CMakeFiles/sample6_unittest.dir/flags.make
CMakeFiles/sample6_unittest.dir/samples/sample6_unittest.cc.o: ../samples/sample6_unittest.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ajbernal/dev/bat/research/gtest-1.7.0/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/sample6_unittest.dir/samples/sample6_unittest.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/sample6_unittest.dir/samples/sample6_unittest.cc.o -c /home/ajbernal/dev/bat/research/gtest-1.7.0/samples/sample6_unittest.cc

CMakeFiles/sample6_unittest.dir/samples/sample6_unittest.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sample6_unittest.dir/samples/sample6_unittest.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ajbernal/dev/bat/research/gtest-1.7.0/samples/sample6_unittest.cc > CMakeFiles/sample6_unittest.dir/samples/sample6_unittest.cc.i

CMakeFiles/sample6_unittest.dir/samples/sample6_unittest.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sample6_unittest.dir/samples/sample6_unittest.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ajbernal/dev/bat/research/gtest-1.7.0/samples/sample6_unittest.cc -o CMakeFiles/sample6_unittest.dir/samples/sample6_unittest.cc.s

CMakeFiles/sample6_unittest.dir/samples/sample6_unittest.cc.o.requires:
.PHONY : CMakeFiles/sample6_unittest.dir/samples/sample6_unittest.cc.o.requires

CMakeFiles/sample6_unittest.dir/samples/sample6_unittest.cc.o.provides: CMakeFiles/sample6_unittest.dir/samples/sample6_unittest.cc.o.requires
	$(MAKE) -f CMakeFiles/sample6_unittest.dir/build.make CMakeFiles/sample6_unittest.dir/samples/sample6_unittest.cc.o.provides.build
.PHONY : CMakeFiles/sample6_unittest.dir/samples/sample6_unittest.cc.o.provides

CMakeFiles/sample6_unittest.dir/samples/sample6_unittest.cc.o.provides.build: CMakeFiles/sample6_unittest.dir/samples/sample6_unittest.cc.o

# Object files for target sample6_unittest
sample6_unittest_OBJECTS = \
"CMakeFiles/sample6_unittest.dir/samples/sample6_unittest.cc.o"

# External object files for target sample6_unittest
sample6_unittest_EXTERNAL_OBJECTS =

sample6_unittest: CMakeFiles/sample6_unittest.dir/samples/sample6_unittest.cc.o
sample6_unittest: CMakeFiles/sample6_unittest.dir/build.make
sample6_unittest: libgtest_main.so
sample6_unittest: libgtest.so
sample6_unittest: CMakeFiles/sample6_unittest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable sample6_unittest"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sample6_unittest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/sample6_unittest.dir/build: sample6_unittest
.PHONY : CMakeFiles/sample6_unittest.dir/build

CMakeFiles/sample6_unittest.dir/requires: CMakeFiles/sample6_unittest.dir/samples/sample6_unittest.cc.o.requires
.PHONY : CMakeFiles/sample6_unittest.dir/requires

CMakeFiles/sample6_unittest.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/sample6_unittest.dir/cmake_clean.cmake
.PHONY : CMakeFiles/sample6_unittest.dir/clean

CMakeFiles/sample6_unittest.dir/depend:
	cd /home/ajbernal/dev/bat/research/gtest-1.7.0/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ajbernal/dev/bat/research/gtest-1.7.0 /home/ajbernal/dev/bat/research/gtest-1.7.0 /home/ajbernal/dev/bat/research/gtest-1.7.0/build /home/ajbernal/dev/bat/research/gtest-1.7.0/build /home/ajbernal/dev/bat/research/gtest-1.7.0/build/CMakeFiles/sample6_unittest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/sample6_unittest.dir/depend

