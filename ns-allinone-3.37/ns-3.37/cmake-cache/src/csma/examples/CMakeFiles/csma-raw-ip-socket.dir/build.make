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
include src/csma/examples/CMakeFiles/csma-raw-ip-socket.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/csma/examples/CMakeFiles/csma-raw-ip-socket.dir/compiler_depend.make

# Include the progress variables for this target.
include src/csma/examples/CMakeFiles/csma-raw-ip-socket.dir/progress.make

# Include the compile flags for this target's objects.
include src/csma/examples/CMakeFiles/csma-raw-ip-socket.dir/flags.make

src/csma/examples/CMakeFiles/csma-raw-ip-socket.dir/csma-raw-ip-socket.cc.o: src/csma/examples/CMakeFiles/csma-raw-ip-socket.dir/flags.make
src/csma/examples/CMakeFiles/csma-raw-ip-socket.dir/csma-raw-ip-socket.cc.o: /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/src/csma/examples/csma-raw-ip-socket.cc
src/csma/examples/CMakeFiles/csma-raw-ip-socket.dir/csma-raw-ip-socket.cc.o: CMakeFiles/stdlib_pch_exec.dir/cmake_pch_arm64.hxx
src/csma/examples/CMakeFiles/csma-raw-ip-socket.dir/csma-raw-ip-socket.cc.o: CMakeFiles/stdlib_pch_exec.dir/cmake_pch_arm64.hxx.pch
src/csma/examples/CMakeFiles/csma-raw-ip-socket.dir/csma-raw-ip-socket.cc.o: src/csma/examples/CMakeFiles/csma-raw-ip-socket.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/csma/examples/CMakeFiles/csma-raw-ip-socket.dir/csma-raw-ip-socket.cc.o"
	cd /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/src/csma/examples && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -Xarch_arm64 -include/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/CMakeFiles/stdlib_pch_exec.dir/cmake_pch_arm64.hxx -MD -MT src/csma/examples/CMakeFiles/csma-raw-ip-socket.dir/csma-raw-ip-socket.cc.o -MF CMakeFiles/csma-raw-ip-socket.dir/csma-raw-ip-socket.cc.o.d -o CMakeFiles/csma-raw-ip-socket.dir/csma-raw-ip-socket.cc.o -c /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/src/csma/examples/csma-raw-ip-socket.cc

src/csma/examples/CMakeFiles/csma-raw-ip-socket.dir/csma-raw-ip-socket.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/csma-raw-ip-socket.dir/csma-raw-ip-socket.cc.i"
	cd /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/src/csma/examples && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -Xarch_arm64 -include/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/CMakeFiles/stdlib_pch_exec.dir/cmake_pch_arm64.hxx -E /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/src/csma/examples/csma-raw-ip-socket.cc > CMakeFiles/csma-raw-ip-socket.dir/csma-raw-ip-socket.cc.i

src/csma/examples/CMakeFiles/csma-raw-ip-socket.dir/csma-raw-ip-socket.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/csma-raw-ip-socket.dir/csma-raw-ip-socket.cc.s"
	cd /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/src/csma/examples && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -Xarch_arm64 -include/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/CMakeFiles/stdlib_pch_exec.dir/cmake_pch_arm64.hxx -S /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/src/csma/examples/csma-raw-ip-socket.cc -o CMakeFiles/csma-raw-ip-socket.dir/csma-raw-ip-socket.cc.s

# Object files for target csma-raw-ip-socket
csma__raw__ip__socket_OBJECTS = \
"CMakeFiles/csma-raw-ip-socket.dir/csma-raw-ip-socket.cc.o"

# External object files for target csma-raw-ip-socket
csma__raw__ip__socket_EXTERNAL_OBJECTS =

/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/build/src/csma/examples/ns3.37-csma-raw-ip-socket-default: src/csma/examples/CMakeFiles/csma-raw-ip-socket.dir/csma-raw-ip-socket.cc.o
/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/build/src/csma/examples/ns3.37-csma-raw-ip-socket-default: src/csma/examples/CMakeFiles/csma-raw-ip-socket.dir/build.make
/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/build/src/csma/examples/ns3.37-csma-raw-ip-socket-default: /Library/Developer/CommandLineTools/SDKs/MacOSX13.1.sdk/usr/lib/libsqlite3.tbd
/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/build/src/csma/examples/ns3.37-csma-raw-ip-socket-default: src/csma/examples/CMakeFiles/csma-raw-ip-socket.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/build/src/csma/examples/ns3.37-csma-raw-ip-socket-default"
	cd /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/src/csma/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/csma-raw-ip-socket.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/csma/examples/CMakeFiles/csma-raw-ip-socket.dir/build: /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/build/src/csma/examples/ns3.37-csma-raw-ip-socket-default
.PHONY : src/csma/examples/CMakeFiles/csma-raw-ip-socket.dir/build

src/csma/examples/CMakeFiles/csma-raw-ip-socket.dir/clean:
	cd /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/src/csma/examples && $(CMAKE_COMMAND) -P CMakeFiles/csma-raw-ip-socket.dir/cmake_clean.cmake
.PHONY : src/csma/examples/CMakeFiles/csma-raw-ip-socket.dir/clean

src/csma/examples/CMakeFiles/csma-raw-ip-socket.dir/depend:
	cd /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37 /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/src/csma/examples /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/src/csma/examples /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/src/csma/examples/CMakeFiles/csma-raw-ip-socket.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/csma/examples/CMakeFiles/csma-raw-ip-socket.dir/depend

