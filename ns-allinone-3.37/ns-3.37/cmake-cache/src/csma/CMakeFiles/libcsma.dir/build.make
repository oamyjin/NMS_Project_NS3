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
include src/csma/CMakeFiles/libcsma.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/csma/CMakeFiles/libcsma.dir/compiler_depend.make

# Include the progress variables for this target.
include src/csma/CMakeFiles/libcsma.dir/progress.make

# Include the compile flags for this target's objects.
include src/csma/CMakeFiles/libcsma.dir/flags.make

# Object files for target libcsma
libcsma_OBJECTS =

# External object files for target libcsma
libcsma_EXTERNAL_OBJECTS = \
"/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/src/csma/CMakeFiles/libcsma-obj.dir/helper/csma-helper.cc.o" \
"/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/src/csma/CMakeFiles/libcsma-obj.dir/model/backoff.cc.o" \
"/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/src/csma/CMakeFiles/libcsma-obj.dir/model/csma-channel.cc.o" \
"/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/src/csma/CMakeFiles/libcsma-obj.dir/model/csma-net-device.cc.o"

/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/build/lib/libns3.37-csma-default.dylib: src/csma/CMakeFiles/libcsma-obj.dir/helper/csma-helper.cc.o
/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/build/lib/libns3.37-csma-default.dylib: src/csma/CMakeFiles/libcsma-obj.dir/model/backoff.cc.o
/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/build/lib/libns3.37-csma-default.dylib: src/csma/CMakeFiles/libcsma-obj.dir/model/csma-channel.cc.o
/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/build/lib/libns3.37-csma-default.dylib: src/csma/CMakeFiles/libcsma-obj.dir/model/csma-net-device.cc.o
/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/build/lib/libns3.37-csma-default.dylib: src/csma/CMakeFiles/libcsma.dir/build.make
/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/build/lib/libns3.37-csma-default.dylib: /Library/Developer/CommandLineTools/SDKs/MacOSX13.1.sdk/usr/lib/libsqlite3.tbd
/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/build/lib/libns3.37-csma-default.dylib: src/csma/CMakeFiles/libcsma.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Linking CXX shared library /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/build/lib/libns3.37-csma-default.dylib"
	cd /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/src/csma && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/libcsma.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/csma/CMakeFiles/libcsma.dir/build: /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/build/lib/libns3.37-csma-default.dylib
.PHONY : src/csma/CMakeFiles/libcsma.dir/build

src/csma/CMakeFiles/libcsma.dir/clean:
	cd /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/src/csma && $(CMAKE_COMMAND) -P CMakeFiles/libcsma.dir/cmake_clean.cmake
.PHONY : src/csma/CMakeFiles/libcsma.dir/clean

src/csma/CMakeFiles/libcsma.dir/depend:
	cd /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37 /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/src/csma /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/src/csma /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/src/csma/CMakeFiles/libcsma.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/csma/CMakeFiles/libcsma.dir/depend

