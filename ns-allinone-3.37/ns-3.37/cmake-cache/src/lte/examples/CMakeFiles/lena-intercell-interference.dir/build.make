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
include src/lte/examples/CMakeFiles/lena-intercell-interference.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/lte/examples/CMakeFiles/lena-intercell-interference.dir/compiler_depend.make

# Include the progress variables for this target.
include src/lte/examples/CMakeFiles/lena-intercell-interference.dir/progress.make

# Include the compile flags for this target's objects.
include src/lte/examples/CMakeFiles/lena-intercell-interference.dir/flags.make

src/lte/examples/CMakeFiles/lena-intercell-interference.dir/lena-intercell-interference.cc.o: src/lte/examples/CMakeFiles/lena-intercell-interference.dir/flags.make
src/lte/examples/CMakeFiles/lena-intercell-interference.dir/lena-intercell-interference.cc.o: /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/src/lte/examples/lena-intercell-interference.cc
src/lte/examples/CMakeFiles/lena-intercell-interference.dir/lena-intercell-interference.cc.o: CMakeFiles/stdlib_pch_exec.dir/cmake_pch_arm64.hxx
src/lte/examples/CMakeFiles/lena-intercell-interference.dir/lena-intercell-interference.cc.o: CMakeFiles/stdlib_pch_exec.dir/cmake_pch_arm64.hxx.pch
src/lte/examples/CMakeFiles/lena-intercell-interference.dir/lena-intercell-interference.cc.o: src/lte/examples/CMakeFiles/lena-intercell-interference.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/lte/examples/CMakeFiles/lena-intercell-interference.dir/lena-intercell-interference.cc.o"
	cd /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/src/lte/examples && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -Xarch_arm64 -include/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/CMakeFiles/stdlib_pch_exec.dir/cmake_pch_arm64.hxx -MD -MT src/lte/examples/CMakeFiles/lena-intercell-interference.dir/lena-intercell-interference.cc.o -MF CMakeFiles/lena-intercell-interference.dir/lena-intercell-interference.cc.o.d -o CMakeFiles/lena-intercell-interference.dir/lena-intercell-interference.cc.o -c /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/src/lte/examples/lena-intercell-interference.cc

src/lte/examples/CMakeFiles/lena-intercell-interference.dir/lena-intercell-interference.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lena-intercell-interference.dir/lena-intercell-interference.cc.i"
	cd /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/src/lte/examples && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -Xarch_arm64 -include/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/CMakeFiles/stdlib_pch_exec.dir/cmake_pch_arm64.hxx -E /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/src/lte/examples/lena-intercell-interference.cc > CMakeFiles/lena-intercell-interference.dir/lena-intercell-interference.cc.i

src/lte/examples/CMakeFiles/lena-intercell-interference.dir/lena-intercell-interference.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lena-intercell-interference.dir/lena-intercell-interference.cc.s"
	cd /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/src/lte/examples && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -Xarch_arm64 -include/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/CMakeFiles/stdlib_pch_exec.dir/cmake_pch_arm64.hxx -S /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/src/lte/examples/lena-intercell-interference.cc -o CMakeFiles/lena-intercell-interference.dir/lena-intercell-interference.cc.s

# Object files for target lena-intercell-interference
lena__intercell__interference_OBJECTS = \
"CMakeFiles/lena-intercell-interference.dir/lena-intercell-interference.cc.o"

# External object files for target lena-intercell-interference
lena__intercell__interference_EXTERNAL_OBJECTS =

/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/build/src/lte/examples/ns3.37-lena-intercell-interference-default: src/lte/examples/CMakeFiles/lena-intercell-interference.dir/lena-intercell-interference.cc.o
/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/build/src/lte/examples/ns3.37-lena-intercell-interference-default: src/lte/examples/CMakeFiles/lena-intercell-interference.dir/build.make
/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/build/src/lte/examples/ns3.37-lena-intercell-interference-default: /Library/Developer/CommandLineTools/SDKs/MacOSX13.1.sdk/usr/lib/libxml2.tbd
/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/build/src/lte/examples/ns3.37-lena-intercell-interference-default: /Library/Developer/CommandLineTools/SDKs/MacOSX13.1.sdk/usr/lib/libsqlite3.tbd
/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/build/src/lte/examples/ns3.37-lena-intercell-interference-default: src/lte/examples/CMakeFiles/lena-intercell-interference.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/build/src/lte/examples/ns3.37-lena-intercell-interference-default"
	cd /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/src/lte/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/lena-intercell-interference.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/lte/examples/CMakeFiles/lena-intercell-interference.dir/build: /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/build/src/lte/examples/ns3.37-lena-intercell-interference-default
.PHONY : src/lte/examples/CMakeFiles/lena-intercell-interference.dir/build

src/lte/examples/CMakeFiles/lena-intercell-interference.dir/clean:
	cd /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/src/lte/examples && $(CMAKE_COMMAND) -P CMakeFiles/lena-intercell-interference.dir/cmake_clean.cmake
.PHONY : src/lte/examples/CMakeFiles/lena-intercell-interference.dir/clean

src/lte/examples/CMakeFiles/lena-intercell-interference.dir/depend:
	cd /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37 /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/src/lte/examples /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/src/lte/examples /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/src/lte/examples/CMakeFiles/lena-intercell-interference.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/lte/examples/CMakeFiles/lena-intercell-interference.dir/depend

