# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.26

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
CMAKE_COMMAND = /Applications/CMake.app/Contents/bin/cmake

# The command to remove a file.
RM = /Applications/CMake.app/Contents/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache

# Utility rule file for doxygen-no-build.

# Include any custom commands dependencies for this target.
include CMakeFiles/doxygen-no-build.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/doxygen-no-build.dir/progress.make

CMakeFiles/doxygen-no-build:
	echo The following Doxygen dependencies are missing: doxygen dot dia. Reconfigure the project after installing them.

doxygen-no-build: CMakeFiles/doxygen-no-build
doxygen-no-build: CMakeFiles/doxygen-no-build.dir/build.make
.PHONY : doxygen-no-build

# Rule to build all files generated by this target.
CMakeFiles/doxygen-no-build.dir/build: doxygen-no-build
.PHONY : CMakeFiles/doxygen-no-build.dir/build

CMakeFiles/doxygen-no-build.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/doxygen-no-build.dir/cmake_clean.cmake
.PHONY : CMakeFiles/doxygen-no-build.dir/clean

CMakeFiles/doxygen-no-build.dir/depend:
	cd /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37 /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37 /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/CMakeFiles/doxygen-no-build.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/doxygen-no-build.dir/depend

