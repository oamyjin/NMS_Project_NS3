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

# Include any dependencies generated for this target.
include CMakeFiles/stdlib_pch.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/stdlib_pch.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/stdlib_pch.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/stdlib_pch.dir/flags.make

CMakeFiles/stdlib_pch.dir/cmake_pch_arm64.hxx.pch: CMakeFiles/stdlib_pch.dir/flags.make
CMakeFiles/stdlib_pch.dir/cmake_pch_arm64.hxx.pch: CMakeFiles/stdlib_pch.dir/cmake_pch_arm64.hxx.cxx
CMakeFiles/stdlib_pch.dir/cmake_pch_arm64.hxx.pch: CMakeFiles/stdlib_pch.dir/cmake_pch_arm64.hxx
CMakeFiles/stdlib_pch.dir/cmake_pch_arm64.hxx.pch: CMakeFiles/stdlib_pch.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/stdlib_pch.dir/cmake_pch_arm64.hxx.pch"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGSarm64) -Winvalid-pch -Xclang -emit-pch -Xclang -include -Xclang /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/CMakeFiles/stdlib_pch.dir/cmake_pch_arm64.hxx -x c++-header -MD -MT CMakeFiles/stdlib_pch.dir/cmake_pch_arm64.hxx.pch -MF CMakeFiles/stdlib_pch.dir/cmake_pch_arm64.hxx.pch.d -o CMakeFiles/stdlib_pch.dir/cmake_pch_arm64.hxx.pch -c /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/CMakeFiles/stdlib_pch.dir/cmake_pch_arm64.hxx.cxx

CMakeFiles/stdlib_pch.dir/cmake_pch_arm64.hxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/stdlib_pch.dir/cmake_pch_arm64.hxx.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGSarm64) -Winvalid-pch -Xclang -emit-pch -Xclang -include -Xclang /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/CMakeFiles/stdlib_pch.dir/cmake_pch_arm64.hxx -x c++-header -E /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/CMakeFiles/stdlib_pch.dir/cmake_pch_arm64.hxx.cxx > CMakeFiles/stdlib_pch.dir/cmake_pch_arm64.hxx.i

CMakeFiles/stdlib_pch.dir/cmake_pch_arm64.hxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/stdlib_pch.dir/cmake_pch_arm64.hxx.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGSarm64) -Winvalid-pch -Xclang -emit-pch -Xclang -include -Xclang /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/CMakeFiles/stdlib_pch.dir/cmake_pch_arm64.hxx -x c++-header -S /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/CMakeFiles/stdlib_pch.dir/cmake_pch_arm64.hxx.cxx -o CMakeFiles/stdlib_pch.dir/cmake_pch_arm64.hxx.s

CMakeFiles/stdlib_pch.dir/build-support/empty.cc.o: CMakeFiles/stdlib_pch.dir/flags.make
CMakeFiles/stdlib_pch.dir/build-support/empty.cc.o: /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/build-support/empty.cc
CMakeFiles/stdlib_pch.dir/build-support/empty.cc.o: CMakeFiles/stdlib_pch.dir/cmake_pch_arm64.hxx
CMakeFiles/stdlib_pch.dir/build-support/empty.cc.o: CMakeFiles/stdlib_pch.dir/cmake_pch_arm64.hxx.pch
CMakeFiles/stdlib_pch.dir/build-support/empty.cc.o: CMakeFiles/stdlib_pch.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/stdlib_pch.dir/build-support/empty.cc.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -Xarch_arm64 -include/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/CMakeFiles/stdlib_pch.dir/cmake_pch_arm64.hxx -MD -MT CMakeFiles/stdlib_pch.dir/build-support/empty.cc.o -MF CMakeFiles/stdlib_pch.dir/build-support/empty.cc.o.d -o CMakeFiles/stdlib_pch.dir/build-support/empty.cc.o -c /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/build-support/empty.cc

CMakeFiles/stdlib_pch.dir/build-support/empty.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/stdlib_pch.dir/build-support/empty.cc.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -Xarch_arm64 -include/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/CMakeFiles/stdlib_pch.dir/cmake_pch_arm64.hxx -E /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/build-support/empty.cc > CMakeFiles/stdlib_pch.dir/build-support/empty.cc.i

CMakeFiles/stdlib_pch.dir/build-support/empty.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/stdlib_pch.dir/build-support/empty.cc.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -Xarch_arm64 -include/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/CMakeFiles/stdlib_pch.dir/cmake_pch_arm64.hxx -S /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/build-support/empty.cc -o CMakeFiles/stdlib_pch.dir/build-support/empty.cc.s

stdlib_pch: CMakeFiles/stdlib_pch.dir/cmake_pch_arm64.hxx.pch
stdlib_pch: CMakeFiles/stdlib_pch.dir/build-support/empty.cc.o
stdlib_pch: CMakeFiles/stdlib_pch.dir/build.make
.PHONY : stdlib_pch

# Rule to build all files generated by this target.
CMakeFiles/stdlib_pch.dir/build: stdlib_pch
.PHONY : CMakeFiles/stdlib_pch.dir/build

CMakeFiles/stdlib_pch.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/stdlib_pch.dir/cmake_clean.cmake
.PHONY : CMakeFiles/stdlib_pch.dir/clean

CMakeFiles/stdlib_pch.dir/depend:
	cd /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37 /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37 /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/CMakeFiles/stdlib_pch.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/stdlib_pch.dir/depend

