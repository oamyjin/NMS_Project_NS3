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
include src/sixlowpan/CMakeFiles/libsixlowpan-test.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/sixlowpan/CMakeFiles/libsixlowpan-test.dir/compiler_depend.make

# Include the progress variables for this target.
include src/sixlowpan/CMakeFiles/libsixlowpan-test.dir/progress.make

# Include the compile flags for this target's objects.
include src/sixlowpan/CMakeFiles/libsixlowpan-test.dir/flags.make

src/sixlowpan/CMakeFiles/libsixlowpan-test.dir/test/sixlowpan-examples-test-suite.cc.o: src/sixlowpan/CMakeFiles/libsixlowpan-test.dir/flags.make
src/sixlowpan/CMakeFiles/libsixlowpan-test.dir/test/sixlowpan-examples-test-suite.cc.o: /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/src/sixlowpan/test/sixlowpan-examples-test-suite.cc
src/sixlowpan/CMakeFiles/libsixlowpan-test.dir/test/sixlowpan-examples-test-suite.cc.o: CMakeFiles/stdlib_pch.dir/cmake_pch_arm64.hxx
src/sixlowpan/CMakeFiles/libsixlowpan-test.dir/test/sixlowpan-examples-test-suite.cc.o: CMakeFiles/stdlib_pch.dir/cmake_pch_arm64.hxx.pch
src/sixlowpan/CMakeFiles/libsixlowpan-test.dir/test/sixlowpan-examples-test-suite.cc.o: src/sixlowpan/CMakeFiles/libsixlowpan-test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/sixlowpan/CMakeFiles/libsixlowpan-test.dir/test/sixlowpan-examples-test-suite.cc.o"
	cd /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/src/sixlowpan && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -Xarch_arm64 -include/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/CMakeFiles/stdlib_pch.dir/cmake_pch_arm64.hxx -MD -MT src/sixlowpan/CMakeFiles/libsixlowpan-test.dir/test/sixlowpan-examples-test-suite.cc.o -MF CMakeFiles/libsixlowpan-test.dir/test/sixlowpan-examples-test-suite.cc.o.d -o CMakeFiles/libsixlowpan-test.dir/test/sixlowpan-examples-test-suite.cc.o -c /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/src/sixlowpan/test/sixlowpan-examples-test-suite.cc

src/sixlowpan/CMakeFiles/libsixlowpan-test.dir/test/sixlowpan-examples-test-suite.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/libsixlowpan-test.dir/test/sixlowpan-examples-test-suite.cc.i"
	cd /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/src/sixlowpan && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -Xarch_arm64 -include/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/CMakeFiles/stdlib_pch.dir/cmake_pch_arm64.hxx -E /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/src/sixlowpan/test/sixlowpan-examples-test-suite.cc > CMakeFiles/libsixlowpan-test.dir/test/sixlowpan-examples-test-suite.cc.i

src/sixlowpan/CMakeFiles/libsixlowpan-test.dir/test/sixlowpan-examples-test-suite.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/libsixlowpan-test.dir/test/sixlowpan-examples-test-suite.cc.s"
	cd /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/src/sixlowpan && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -Xarch_arm64 -include/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/CMakeFiles/stdlib_pch.dir/cmake_pch_arm64.hxx -S /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/src/sixlowpan/test/sixlowpan-examples-test-suite.cc -o CMakeFiles/libsixlowpan-test.dir/test/sixlowpan-examples-test-suite.cc.s

src/sixlowpan/CMakeFiles/libsixlowpan-test.dir/test/mock-net-device.cc.o: src/sixlowpan/CMakeFiles/libsixlowpan-test.dir/flags.make
src/sixlowpan/CMakeFiles/libsixlowpan-test.dir/test/mock-net-device.cc.o: /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/src/sixlowpan/test/mock-net-device.cc
src/sixlowpan/CMakeFiles/libsixlowpan-test.dir/test/mock-net-device.cc.o: CMakeFiles/stdlib_pch.dir/cmake_pch_arm64.hxx
src/sixlowpan/CMakeFiles/libsixlowpan-test.dir/test/mock-net-device.cc.o: CMakeFiles/stdlib_pch.dir/cmake_pch_arm64.hxx.pch
src/sixlowpan/CMakeFiles/libsixlowpan-test.dir/test/mock-net-device.cc.o: src/sixlowpan/CMakeFiles/libsixlowpan-test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/sixlowpan/CMakeFiles/libsixlowpan-test.dir/test/mock-net-device.cc.o"
	cd /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/src/sixlowpan && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -Xarch_arm64 -include/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/CMakeFiles/stdlib_pch.dir/cmake_pch_arm64.hxx -MD -MT src/sixlowpan/CMakeFiles/libsixlowpan-test.dir/test/mock-net-device.cc.o -MF CMakeFiles/libsixlowpan-test.dir/test/mock-net-device.cc.o.d -o CMakeFiles/libsixlowpan-test.dir/test/mock-net-device.cc.o -c /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/src/sixlowpan/test/mock-net-device.cc

src/sixlowpan/CMakeFiles/libsixlowpan-test.dir/test/mock-net-device.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/libsixlowpan-test.dir/test/mock-net-device.cc.i"
	cd /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/src/sixlowpan && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -Xarch_arm64 -include/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/CMakeFiles/stdlib_pch.dir/cmake_pch_arm64.hxx -E /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/src/sixlowpan/test/mock-net-device.cc > CMakeFiles/libsixlowpan-test.dir/test/mock-net-device.cc.i

src/sixlowpan/CMakeFiles/libsixlowpan-test.dir/test/mock-net-device.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/libsixlowpan-test.dir/test/mock-net-device.cc.s"
	cd /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/src/sixlowpan && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -Xarch_arm64 -include/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/CMakeFiles/stdlib_pch.dir/cmake_pch_arm64.hxx -S /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/src/sixlowpan/test/mock-net-device.cc -o CMakeFiles/libsixlowpan-test.dir/test/mock-net-device.cc.s

src/sixlowpan/CMakeFiles/libsixlowpan-test.dir/test/sixlowpan-fragmentation-test.cc.o: src/sixlowpan/CMakeFiles/libsixlowpan-test.dir/flags.make
src/sixlowpan/CMakeFiles/libsixlowpan-test.dir/test/sixlowpan-fragmentation-test.cc.o: /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/src/sixlowpan/test/sixlowpan-fragmentation-test.cc
src/sixlowpan/CMakeFiles/libsixlowpan-test.dir/test/sixlowpan-fragmentation-test.cc.o: CMakeFiles/stdlib_pch.dir/cmake_pch_arm64.hxx
src/sixlowpan/CMakeFiles/libsixlowpan-test.dir/test/sixlowpan-fragmentation-test.cc.o: CMakeFiles/stdlib_pch.dir/cmake_pch_arm64.hxx.pch
src/sixlowpan/CMakeFiles/libsixlowpan-test.dir/test/sixlowpan-fragmentation-test.cc.o: src/sixlowpan/CMakeFiles/libsixlowpan-test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/sixlowpan/CMakeFiles/libsixlowpan-test.dir/test/sixlowpan-fragmentation-test.cc.o"
	cd /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/src/sixlowpan && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -Xarch_arm64 -include/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/CMakeFiles/stdlib_pch.dir/cmake_pch_arm64.hxx -MD -MT src/sixlowpan/CMakeFiles/libsixlowpan-test.dir/test/sixlowpan-fragmentation-test.cc.o -MF CMakeFiles/libsixlowpan-test.dir/test/sixlowpan-fragmentation-test.cc.o.d -o CMakeFiles/libsixlowpan-test.dir/test/sixlowpan-fragmentation-test.cc.o -c /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/src/sixlowpan/test/sixlowpan-fragmentation-test.cc

src/sixlowpan/CMakeFiles/libsixlowpan-test.dir/test/sixlowpan-fragmentation-test.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/libsixlowpan-test.dir/test/sixlowpan-fragmentation-test.cc.i"
	cd /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/src/sixlowpan && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -Xarch_arm64 -include/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/CMakeFiles/stdlib_pch.dir/cmake_pch_arm64.hxx -E /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/src/sixlowpan/test/sixlowpan-fragmentation-test.cc > CMakeFiles/libsixlowpan-test.dir/test/sixlowpan-fragmentation-test.cc.i

src/sixlowpan/CMakeFiles/libsixlowpan-test.dir/test/sixlowpan-fragmentation-test.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/libsixlowpan-test.dir/test/sixlowpan-fragmentation-test.cc.s"
	cd /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/src/sixlowpan && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -Xarch_arm64 -include/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/CMakeFiles/stdlib_pch.dir/cmake_pch_arm64.hxx -S /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/src/sixlowpan/test/sixlowpan-fragmentation-test.cc -o CMakeFiles/libsixlowpan-test.dir/test/sixlowpan-fragmentation-test.cc.s

src/sixlowpan/CMakeFiles/libsixlowpan-test.dir/test/sixlowpan-hc1-test.cc.o: src/sixlowpan/CMakeFiles/libsixlowpan-test.dir/flags.make
src/sixlowpan/CMakeFiles/libsixlowpan-test.dir/test/sixlowpan-hc1-test.cc.o: /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/src/sixlowpan/test/sixlowpan-hc1-test.cc
src/sixlowpan/CMakeFiles/libsixlowpan-test.dir/test/sixlowpan-hc1-test.cc.o: CMakeFiles/stdlib_pch.dir/cmake_pch_arm64.hxx
src/sixlowpan/CMakeFiles/libsixlowpan-test.dir/test/sixlowpan-hc1-test.cc.o: CMakeFiles/stdlib_pch.dir/cmake_pch_arm64.hxx.pch
src/sixlowpan/CMakeFiles/libsixlowpan-test.dir/test/sixlowpan-hc1-test.cc.o: src/sixlowpan/CMakeFiles/libsixlowpan-test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object src/sixlowpan/CMakeFiles/libsixlowpan-test.dir/test/sixlowpan-hc1-test.cc.o"
	cd /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/src/sixlowpan && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -Xarch_arm64 -include/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/CMakeFiles/stdlib_pch.dir/cmake_pch_arm64.hxx -MD -MT src/sixlowpan/CMakeFiles/libsixlowpan-test.dir/test/sixlowpan-hc1-test.cc.o -MF CMakeFiles/libsixlowpan-test.dir/test/sixlowpan-hc1-test.cc.o.d -o CMakeFiles/libsixlowpan-test.dir/test/sixlowpan-hc1-test.cc.o -c /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/src/sixlowpan/test/sixlowpan-hc1-test.cc

src/sixlowpan/CMakeFiles/libsixlowpan-test.dir/test/sixlowpan-hc1-test.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/libsixlowpan-test.dir/test/sixlowpan-hc1-test.cc.i"
	cd /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/src/sixlowpan && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -Xarch_arm64 -include/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/CMakeFiles/stdlib_pch.dir/cmake_pch_arm64.hxx -E /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/src/sixlowpan/test/sixlowpan-hc1-test.cc > CMakeFiles/libsixlowpan-test.dir/test/sixlowpan-hc1-test.cc.i

src/sixlowpan/CMakeFiles/libsixlowpan-test.dir/test/sixlowpan-hc1-test.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/libsixlowpan-test.dir/test/sixlowpan-hc1-test.cc.s"
	cd /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/src/sixlowpan && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -Xarch_arm64 -include/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/CMakeFiles/stdlib_pch.dir/cmake_pch_arm64.hxx -S /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/src/sixlowpan/test/sixlowpan-hc1-test.cc -o CMakeFiles/libsixlowpan-test.dir/test/sixlowpan-hc1-test.cc.s

src/sixlowpan/CMakeFiles/libsixlowpan-test.dir/test/sixlowpan-iphc-stateful-test.cc.o: src/sixlowpan/CMakeFiles/libsixlowpan-test.dir/flags.make
src/sixlowpan/CMakeFiles/libsixlowpan-test.dir/test/sixlowpan-iphc-stateful-test.cc.o: /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/src/sixlowpan/test/sixlowpan-iphc-stateful-test.cc
src/sixlowpan/CMakeFiles/libsixlowpan-test.dir/test/sixlowpan-iphc-stateful-test.cc.o: CMakeFiles/stdlib_pch.dir/cmake_pch_arm64.hxx
src/sixlowpan/CMakeFiles/libsixlowpan-test.dir/test/sixlowpan-iphc-stateful-test.cc.o: CMakeFiles/stdlib_pch.dir/cmake_pch_arm64.hxx.pch
src/sixlowpan/CMakeFiles/libsixlowpan-test.dir/test/sixlowpan-iphc-stateful-test.cc.o: src/sixlowpan/CMakeFiles/libsixlowpan-test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object src/sixlowpan/CMakeFiles/libsixlowpan-test.dir/test/sixlowpan-iphc-stateful-test.cc.o"
	cd /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/src/sixlowpan && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -Xarch_arm64 -include/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/CMakeFiles/stdlib_pch.dir/cmake_pch_arm64.hxx -MD -MT src/sixlowpan/CMakeFiles/libsixlowpan-test.dir/test/sixlowpan-iphc-stateful-test.cc.o -MF CMakeFiles/libsixlowpan-test.dir/test/sixlowpan-iphc-stateful-test.cc.o.d -o CMakeFiles/libsixlowpan-test.dir/test/sixlowpan-iphc-stateful-test.cc.o -c /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/src/sixlowpan/test/sixlowpan-iphc-stateful-test.cc

src/sixlowpan/CMakeFiles/libsixlowpan-test.dir/test/sixlowpan-iphc-stateful-test.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/libsixlowpan-test.dir/test/sixlowpan-iphc-stateful-test.cc.i"
	cd /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/src/sixlowpan && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -Xarch_arm64 -include/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/CMakeFiles/stdlib_pch.dir/cmake_pch_arm64.hxx -E /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/src/sixlowpan/test/sixlowpan-iphc-stateful-test.cc > CMakeFiles/libsixlowpan-test.dir/test/sixlowpan-iphc-stateful-test.cc.i

src/sixlowpan/CMakeFiles/libsixlowpan-test.dir/test/sixlowpan-iphc-stateful-test.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/libsixlowpan-test.dir/test/sixlowpan-iphc-stateful-test.cc.s"
	cd /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/src/sixlowpan && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -Xarch_arm64 -include/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/CMakeFiles/stdlib_pch.dir/cmake_pch_arm64.hxx -S /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/src/sixlowpan/test/sixlowpan-iphc-stateful-test.cc -o CMakeFiles/libsixlowpan-test.dir/test/sixlowpan-iphc-stateful-test.cc.s

src/sixlowpan/CMakeFiles/libsixlowpan-test.dir/test/sixlowpan-iphc-test.cc.o: src/sixlowpan/CMakeFiles/libsixlowpan-test.dir/flags.make
src/sixlowpan/CMakeFiles/libsixlowpan-test.dir/test/sixlowpan-iphc-test.cc.o: /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/src/sixlowpan/test/sixlowpan-iphc-test.cc
src/sixlowpan/CMakeFiles/libsixlowpan-test.dir/test/sixlowpan-iphc-test.cc.o: CMakeFiles/stdlib_pch.dir/cmake_pch_arm64.hxx
src/sixlowpan/CMakeFiles/libsixlowpan-test.dir/test/sixlowpan-iphc-test.cc.o: CMakeFiles/stdlib_pch.dir/cmake_pch_arm64.hxx.pch
src/sixlowpan/CMakeFiles/libsixlowpan-test.dir/test/sixlowpan-iphc-test.cc.o: src/sixlowpan/CMakeFiles/libsixlowpan-test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object src/sixlowpan/CMakeFiles/libsixlowpan-test.dir/test/sixlowpan-iphc-test.cc.o"
	cd /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/src/sixlowpan && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -Xarch_arm64 -include/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/CMakeFiles/stdlib_pch.dir/cmake_pch_arm64.hxx -MD -MT src/sixlowpan/CMakeFiles/libsixlowpan-test.dir/test/sixlowpan-iphc-test.cc.o -MF CMakeFiles/libsixlowpan-test.dir/test/sixlowpan-iphc-test.cc.o.d -o CMakeFiles/libsixlowpan-test.dir/test/sixlowpan-iphc-test.cc.o -c /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/src/sixlowpan/test/sixlowpan-iphc-test.cc

src/sixlowpan/CMakeFiles/libsixlowpan-test.dir/test/sixlowpan-iphc-test.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/libsixlowpan-test.dir/test/sixlowpan-iphc-test.cc.i"
	cd /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/src/sixlowpan && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -Xarch_arm64 -include/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/CMakeFiles/stdlib_pch.dir/cmake_pch_arm64.hxx -E /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/src/sixlowpan/test/sixlowpan-iphc-test.cc > CMakeFiles/libsixlowpan-test.dir/test/sixlowpan-iphc-test.cc.i

src/sixlowpan/CMakeFiles/libsixlowpan-test.dir/test/sixlowpan-iphc-test.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/libsixlowpan-test.dir/test/sixlowpan-iphc-test.cc.s"
	cd /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/src/sixlowpan && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -Xarch_arm64 -include/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/CMakeFiles/stdlib_pch.dir/cmake_pch_arm64.hxx -S /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/src/sixlowpan/test/sixlowpan-iphc-test.cc -o CMakeFiles/libsixlowpan-test.dir/test/sixlowpan-iphc-test.cc.s

# Object files for target libsixlowpan-test
libsixlowpan__test_OBJECTS = \
"CMakeFiles/libsixlowpan-test.dir/test/sixlowpan-examples-test-suite.cc.o" \
"CMakeFiles/libsixlowpan-test.dir/test/mock-net-device.cc.o" \
"CMakeFiles/libsixlowpan-test.dir/test/sixlowpan-fragmentation-test.cc.o" \
"CMakeFiles/libsixlowpan-test.dir/test/sixlowpan-hc1-test.cc.o" \
"CMakeFiles/libsixlowpan-test.dir/test/sixlowpan-iphc-stateful-test.cc.o" \
"CMakeFiles/libsixlowpan-test.dir/test/sixlowpan-iphc-test.cc.o"

# External object files for target libsixlowpan-test
libsixlowpan__test_EXTERNAL_OBJECTS =

/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/build/lib/libns3.37-sixlowpan-test-default.dylib: src/sixlowpan/CMakeFiles/libsixlowpan-test.dir/test/sixlowpan-examples-test-suite.cc.o
/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/build/lib/libns3.37-sixlowpan-test-default.dylib: src/sixlowpan/CMakeFiles/libsixlowpan-test.dir/test/mock-net-device.cc.o
/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/build/lib/libns3.37-sixlowpan-test-default.dylib: src/sixlowpan/CMakeFiles/libsixlowpan-test.dir/test/sixlowpan-fragmentation-test.cc.o
/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/build/lib/libns3.37-sixlowpan-test-default.dylib: src/sixlowpan/CMakeFiles/libsixlowpan-test.dir/test/sixlowpan-hc1-test.cc.o
/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/build/lib/libns3.37-sixlowpan-test-default.dylib: src/sixlowpan/CMakeFiles/libsixlowpan-test.dir/test/sixlowpan-iphc-stateful-test.cc.o
/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/build/lib/libns3.37-sixlowpan-test-default.dylib: src/sixlowpan/CMakeFiles/libsixlowpan-test.dir/test/sixlowpan-iphc-test.cc.o
/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/build/lib/libns3.37-sixlowpan-test-default.dylib: src/sixlowpan/CMakeFiles/libsixlowpan-test.dir/build.make
/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/build/lib/libns3.37-sixlowpan-test-default.dylib: /Library/Developer/CommandLineTools/SDKs/MacOSX13.1.sdk/usr/lib/libsqlite3.tbd
/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/build/lib/libns3.37-sixlowpan-test-default.dylib: src/sixlowpan/CMakeFiles/libsixlowpan-test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX shared library /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/build/lib/libns3.37-sixlowpan-test-default.dylib"
	cd /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/src/sixlowpan && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/libsixlowpan-test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/sixlowpan/CMakeFiles/libsixlowpan-test.dir/build: /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/build/lib/libns3.37-sixlowpan-test-default.dylib
.PHONY : src/sixlowpan/CMakeFiles/libsixlowpan-test.dir/build

src/sixlowpan/CMakeFiles/libsixlowpan-test.dir/clean:
	cd /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/src/sixlowpan && $(CMAKE_COMMAND) -P CMakeFiles/libsixlowpan-test.dir/cmake_clean.cmake
.PHONY : src/sixlowpan/CMakeFiles/libsixlowpan-test.dir/clean

src/sixlowpan/CMakeFiles/libsixlowpan-test.dir/depend:
	cd /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37 /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/src/sixlowpan /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/src/sixlowpan /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/src/sixlowpan/CMakeFiles/libsixlowpan-test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/sixlowpan/CMakeFiles/libsixlowpan-test.dir/depend

