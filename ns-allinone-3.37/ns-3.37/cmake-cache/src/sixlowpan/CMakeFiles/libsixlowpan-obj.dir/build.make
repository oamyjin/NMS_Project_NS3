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
include src/sixlowpan/CMakeFiles/libsixlowpan-obj.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/sixlowpan/CMakeFiles/libsixlowpan-obj.dir/compiler_depend.make

# Include the progress variables for this target.
include src/sixlowpan/CMakeFiles/libsixlowpan-obj.dir/progress.make

# Include the compile flags for this target's objects.
include src/sixlowpan/CMakeFiles/libsixlowpan-obj.dir/flags.make

src/sixlowpan/CMakeFiles/libsixlowpan-obj.dir/helper/sixlowpan-helper.cc.o: src/sixlowpan/CMakeFiles/libsixlowpan-obj.dir/flags.make
src/sixlowpan/CMakeFiles/libsixlowpan-obj.dir/helper/sixlowpan-helper.cc.o: /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/src/sixlowpan/helper/sixlowpan-helper.cc
src/sixlowpan/CMakeFiles/libsixlowpan-obj.dir/helper/sixlowpan-helper.cc.o: CMakeFiles/stdlib_pch.dir/cmake_pch_arm64.hxx
src/sixlowpan/CMakeFiles/libsixlowpan-obj.dir/helper/sixlowpan-helper.cc.o: CMakeFiles/stdlib_pch.dir/cmake_pch_arm64.hxx.pch
src/sixlowpan/CMakeFiles/libsixlowpan-obj.dir/helper/sixlowpan-helper.cc.o: src/sixlowpan/CMakeFiles/libsixlowpan-obj.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/sixlowpan/CMakeFiles/libsixlowpan-obj.dir/helper/sixlowpan-helper.cc.o"
	cd /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/src/sixlowpan && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -Xarch_arm64 -include/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/CMakeFiles/stdlib_pch.dir/cmake_pch_arm64.hxx -MD -MT src/sixlowpan/CMakeFiles/libsixlowpan-obj.dir/helper/sixlowpan-helper.cc.o -MF CMakeFiles/libsixlowpan-obj.dir/helper/sixlowpan-helper.cc.o.d -o CMakeFiles/libsixlowpan-obj.dir/helper/sixlowpan-helper.cc.o -c /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/src/sixlowpan/helper/sixlowpan-helper.cc

src/sixlowpan/CMakeFiles/libsixlowpan-obj.dir/helper/sixlowpan-helper.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/libsixlowpan-obj.dir/helper/sixlowpan-helper.cc.i"
	cd /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/src/sixlowpan && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -Xarch_arm64 -include/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/CMakeFiles/stdlib_pch.dir/cmake_pch_arm64.hxx -E /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/src/sixlowpan/helper/sixlowpan-helper.cc > CMakeFiles/libsixlowpan-obj.dir/helper/sixlowpan-helper.cc.i

src/sixlowpan/CMakeFiles/libsixlowpan-obj.dir/helper/sixlowpan-helper.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/libsixlowpan-obj.dir/helper/sixlowpan-helper.cc.s"
	cd /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/src/sixlowpan && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -Xarch_arm64 -include/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/CMakeFiles/stdlib_pch.dir/cmake_pch_arm64.hxx -S /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/src/sixlowpan/helper/sixlowpan-helper.cc -o CMakeFiles/libsixlowpan-obj.dir/helper/sixlowpan-helper.cc.s

src/sixlowpan/CMakeFiles/libsixlowpan-obj.dir/model/sixlowpan-header.cc.o: src/sixlowpan/CMakeFiles/libsixlowpan-obj.dir/flags.make
src/sixlowpan/CMakeFiles/libsixlowpan-obj.dir/model/sixlowpan-header.cc.o: /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/src/sixlowpan/model/sixlowpan-header.cc
src/sixlowpan/CMakeFiles/libsixlowpan-obj.dir/model/sixlowpan-header.cc.o: CMakeFiles/stdlib_pch.dir/cmake_pch_arm64.hxx
src/sixlowpan/CMakeFiles/libsixlowpan-obj.dir/model/sixlowpan-header.cc.o: CMakeFiles/stdlib_pch.dir/cmake_pch_arm64.hxx.pch
src/sixlowpan/CMakeFiles/libsixlowpan-obj.dir/model/sixlowpan-header.cc.o: src/sixlowpan/CMakeFiles/libsixlowpan-obj.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/sixlowpan/CMakeFiles/libsixlowpan-obj.dir/model/sixlowpan-header.cc.o"
	cd /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/src/sixlowpan && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -Xarch_arm64 -include/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/CMakeFiles/stdlib_pch.dir/cmake_pch_arm64.hxx -MD -MT src/sixlowpan/CMakeFiles/libsixlowpan-obj.dir/model/sixlowpan-header.cc.o -MF CMakeFiles/libsixlowpan-obj.dir/model/sixlowpan-header.cc.o.d -o CMakeFiles/libsixlowpan-obj.dir/model/sixlowpan-header.cc.o -c /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/src/sixlowpan/model/sixlowpan-header.cc

src/sixlowpan/CMakeFiles/libsixlowpan-obj.dir/model/sixlowpan-header.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/libsixlowpan-obj.dir/model/sixlowpan-header.cc.i"
	cd /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/src/sixlowpan && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -Xarch_arm64 -include/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/CMakeFiles/stdlib_pch.dir/cmake_pch_arm64.hxx -E /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/src/sixlowpan/model/sixlowpan-header.cc > CMakeFiles/libsixlowpan-obj.dir/model/sixlowpan-header.cc.i

src/sixlowpan/CMakeFiles/libsixlowpan-obj.dir/model/sixlowpan-header.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/libsixlowpan-obj.dir/model/sixlowpan-header.cc.s"
	cd /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/src/sixlowpan && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -Xarch_arm64 -include/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/CMakeFiles/stdlib_pch.dir/cmake_pch_arm64.hxx -S /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/src/sixlowpan/model/sixlowpan-header.cc -o CMakeFiles/libsixlowpan-obj.dir/model/sixlowpan-header.cc.s

src/sixlowpan/CMakeFiles/libsixlowpan-obj.dir/model/sixlowpan-net-device.cc.o: src/sixlowpan/CMakeFiles/libsixlowpan-obj.dir/flags.make
src/sixlowpan/CMakeFiles/libsixlowpan-obj.dir/model/sixlowpan-net-device.cc.o: /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/src/sixlowpan/model/sixlowpan-net-device.cc
src/sixlowpan/CMakeFiles/libsixlowpan-obj.dir/model/sixlowpan-net-device.cc.o: CMakeFiles/stdlib_pch.dir/cmake_pch_arm64.hxx
src/sixlowpan/CMakeFiles/libsixlowpan-obj.dir/model/sixlowpan-net-device.cc.o: CMakeFiles/stdlib_pch.dir/cmake_pch_arm64.hxx.pch
src/sixlowpan/CMakeFiles/libsixlowpan-obj.dir/model/sixlowpan-net-device.cc.o: src/sixlowpan/CMakeFiles/libsixlowpan-obj.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/sixlowpan/CMakeFiles/libsixlowpan-obj.dir/model/sixlowpan-net-device.cc.o"
	cd /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/src/sixlowpan && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -Xarch_arm64 -include/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/CMakeFiles/stdlib_pch.dir/cmake_pch_arm64.hxx -MD -MT src/sixlowpan/CMakeFiles/libsixlowpan-obj.dir/model/sixlowpan-net-device.cc.o -MF CMakeFiles/libsixlowpan-obj.dir/model/sixlowpan-net-device.cc.o.d -o CMakeFiles/libsixlowpan-obj.dir/model/sixlowpan-net-device.cc.o -c /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/src/sixlowpan/model/sixlowpan-net-device.cc

src/sixlowpan/CMakeFiles/libsixlowpan-obj.dir/model/sixlowpan-net-device.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/libsixlowpan-obj.dir/model/sixlowpan-net-device.cc.i"
	cd /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/src/sixlowpan && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -Xarch_arm64 -include/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/CMakeFiles/stdlib_pch.dir/cmake_pch_arm64.hxx -E /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/src/sixlowpan/model/sixlowpan-net-device.cc > CMakeFiles/libsixlowpan-obj.dir/model/sixlowpan-net-device.cc.i

src/sixlowpan/CMakeFiles/libsixlowpan-obj.dir/model/sixlowpan-net-device.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/libsixlowpan-obj.dir/model/sixlowpan-net-device.cc.s"
	cd /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/src/sixlowpan && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -Xarch_arm64 -include/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/CMakeFiles/stdlib_pch.dir/cmake_pch_arm64.hxx -S /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/src/sixlowpan/model/sixlowpan-net-device.cc -o CMakeFiles/libsixlowpan-obj.dir/model/sixlowpan-net-device.cc.s

libsixlowpan-obj: src/sixlowpan/CMakeFiles/libsixlowpan-obj.dir/helper/sixlowpan-helper.cc.o
libsixlowpan-obj: src/sixlowpan/CMakeFiles/libsixlowpan-obj.dir/model/sixlowpan-header.cc.o
libsixlowpan-obj: src/sixlowpan/CMakeFiles/libsixlowpan-obj.dir/model/sixlowpan-net-device.cc.o
libsixlowpan-obj: src/sixlowpan/CMakeFiles/libsixlowpan-obj.dir/build.make
.PHONY : libsixlowpan-obj

# Rule to build all files generated by this target.
src/sixlowpan/CMakeFiles/libsixlowpan-obj.dir/build: libsixlowpan-obj
.PHONY : src/sixlowpan/CMakeFiles/libsixlowpan-obj.dir/build

src/sixlowpan/CMakeFiles/libsixlowpan-obj.dir/clean:
	cd /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/src/sixlowpan && $(CMAKE_COMMAND) -P CMakeFiles/libsixlowpan-obj.dir/cmake_clean.cmake
.PHONY : src/sixlowpan/CMakeFiles/libsixlowpan-obj.dir/clean

src/sixlowpan/CMakeFiles/libsixlowpan-obj.dir/depend:
	cd /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37 /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/src/sixlowpan /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/src/sixlowpan /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/src/sixlowpan/CMakeFiles/libsixlowpan-obj.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/sixlowpan/CMakeFiles/libsixlowpan-obj.dir/depend

