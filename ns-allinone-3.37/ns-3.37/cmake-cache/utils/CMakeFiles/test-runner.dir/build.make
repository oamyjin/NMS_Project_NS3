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
include utils/CMakeFiles/test-runner.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include utils/CMakeFiles/test-runner.dir/compiler_depend.make

# Include the progress variables for this target.
include utils/CMakeFiles/test-runner.dir/progress.make

# Include the compile flags for this target's objects.
include utils/CMakeFiles/test-runner.dir/flags.make

utils/CMakeFiles/test-runner.dir/test-runner.cc.o: utils/CMakeFiles/test-runner.dir/flags.make
utils/CMakeFiles/test-runner.dir/test-runner.cc.o: /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/utils/test-runner.cc
utils/CMakeFiles/test-runner.dir/test-runner.cc.o: utils/CMakeFiles/test-runner.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object utils/CMakeFiles/test-runner.dir/test-runner.cc.o"
	cd /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/utils && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT utils/CMakeFiles/test-runner.dir/test-runner.cc.o -MF CMakeFiles/test-runner.dir/test-runner.cc.o.d -o CMakeFiles/test-runner.dir/test-runner.cc.o -c /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/utils/test-runner.cc

utils/CMakeFiles/test-runner.dir/test-runner.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test-runner.dir/test-runner.cc.i"
	cd /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/utils && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/utils/test-runner.cc > CMakeFiles/test-runner.dir/test-runner.cc.i

utils/CMakeFiles/test-runner.dir/test-runner.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test-runner.dir/test-runner.cc.s"
	cd /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/utils && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/utils/test-runner.cc -o CMakeFiles/test-runner.dir/test-runner.cc.s

# Object files for target test-runner
test__runner_OBJECTS = \
"CMakeFiles/test-runner.dir/test-runner.cc.o"

# External object files for target test-runner
test__runner_EXTERNAL_OBJECTS = \
"/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/src/test/CMakeFiles/libtest.dir/__/__/build-support/empty.cc.o" \
"/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/src/test/CMakeFiles/libtest.dir/ns3tcp/ns3tcp-loss-test-suite.cc.o" \
"/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/src/test/CMakeFiles/libtest.dir/ns3tcp/ns3tcp-no-delay-test-suite.cc.o" \
"/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/src/test/CMakeFiles/libtest.dir/ns3tcp/ns3tcp-socket-test-suite.cc.o" \
"/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/src/test/CMakeFiles/libtest.dir/ns3tcp/ns3tcp-state-test-suite.cc.o" \
"/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/src/test/CMakeFiles/libtest.dir/csma-system-test-suite.cc.o" \
"/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/src/test/CMakeFiles/libtest.dir/traced/traced-callback-typedef-test-suite.cc.o" \
"/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/src/test/CMakeFiles/libtest.dir/ns3tcp/ns3tcp-socket-writer.cc.o" \
"/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/src/test/CMakeFiles/libtest.dir/traced/traced-value-callback-typedef-test-suite.cc.o" \
"/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/src/test/CMakeFiles/libtest.dir/ns3tc/fq-cobalt-queue-disc-test-suite.cc.o" \
"/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/src/test/CMakeFiles/libtest.dir/ns3tc/fq-codel-queue-disc-test-suite.cc.o" \
"/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/src/test/CMakeFiles/libtest.dir/ns3tc/fq-pie-queue-disc-test-suite.cc.o" \
"/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/src/test/CMakeFiles/libtest.dir/ns3tc/pfifo-fast-queue-disc-test-suite.cc.o" \
"/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/src/test/CMakeFiles/libtest.dir/ns3wifi/wifi-issue-211-test-suite.cc.o" \
"/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/src/test/CMakeFiles/libtest.dir/ns3wifi/wifi-ac-mapping-test-suite.cc.o" \
"/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/src/test/CMakeFiles/libtest.dir/ns3wifi/wifi-msdu-aggregator-test-suite.cc.o"

/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/build/utils/ns3.37-test-runner-default: utils/CMakeFiles/test-runner.dir/test-runner.cc.o
/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/build/utils/ns3.37-test-runner-default: src/test/CMakeFiles/libtest.dir/__/__/build-support/empty.cc.o
/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/build/utils/ns3.37-test-runner-default: src/test/CMakeFiles/libtest.dir/ns3tcp/ns3tcp-loss-test-suite.cc.o
/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/build/utils/ns3.37-test-runner-default: src/test/CMakeFiles/libtest.dir/ns3tcp/ns3tcp-no-delay-test-suite.cc.o
/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/build/utils/ns3.37-test-runner-default: src/test/CMakeFiles/libtest.dir/ns3tcp/ns3tcp-socket-test-suite.cc.o
/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/build/utils/ns3.37-test-runner-default: src/test/CMakeFiles/libtest.dir/ns3tcp/ns3tcp-state-test-suite.cc.o
/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/build/utils/ns3.37-test-runner-default: src/test/CMakeFiles/libtest.dir/csma-system-test-suite.cc.o
/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/build/utils/ns3.37-test-runner-default: src/test/CMakeFiles/libtest.dir/traced/traced-callback-typedef-test-suite.cc.o
/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/build/utils/ns3.37-test-runner-default: src/test/CMakeFiles/libtest.dir/ns3tcp/ns3tcp-socket-writer.cc.o
/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/build/utils/ns3.37-test-runner-default: src/test/CMakeFiles/libtest.dir/traced/traced-value-callback-typedef-test-suite.cc.o
/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/build/utils/ns3.37-test-runner-default: src/test/CMakeFiles/libtest.dir/ns3tc/fq-cobalt-queue-disc-test-suite.cc.o
/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/build/utils/ns3.37-test-runner-default: src/test/CMakeFiles/libtest.dir/ns3tc/fq-codel-queue-disc-test-suite.cc.o
/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/build/utils/ns3.37-test-runner-default: src/test/CMakeFiles/libtest.dir/ns3tc/fq-pie-queue-disc-test-suite.cc.o
/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/build/utils/ns3.37-test-runner-default: src/test/CMakeFiles/libtest.dir/ns3tc/pfifo-fast-queue-disc-test-suite.cc.o
/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/build/utils/ns3.37-test-runner-default: src/test/CMakeFiles/libtest.dir/ns3wifi/wifi-issue-211-test-suite.cc.o
/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/build/utils/ns3.37-test-runner-default: src/test/CMakeFiles/libtest.dir/ns3wifi/wifi-ac-mapping-test-suite.cc.o
/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/build/utils/ns3.37-test-runner-default: src/test/CMakeFiles/libtest.dir/ns3wifi/wifi-msdu-aggregator-test-suite.cc.o
/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/build/utils/ns3.37-test-runner-default: utils/CMakeFiles/test-runner.dir/build.make
/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/build/utils/ns3.37-test-runner-default: /Library/Developer/CommandLineTools/SDKs/MacOSX13.1.sdk/usr/lib/libxml2.tbd
/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/build/utils/ns3.37-test-runner-default: /Library/Developer/CommandLineTools/SDKs/MacOSX13.1.sdk/usr/lib/libsqlite3.tbd
/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/build/utils/ns3.37-test-runner-default: utils/CMakeFiles/test-runner.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/build/utils/ns3.37-test-runner-default"
	cd /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/utils && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test-runner.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
utils/CMakeFiles/test-runner.dir/build: /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/build/utils/ns3.37-test-runner-default
.PHONY : utils/CMakeFiles/test-runner.dir/build

utils/CMakeFiles/test-runner.dir/clean:
	cd /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/utils && $(CMAKE_COMMAND) -P CMakeFiles/test-runner.dir/cmake_clean.cmake
.PHONY : utils/CMakeFiles/test-runner.dir/clean

utils/CMakeFiles/test-runner.dir/depend:
	cd /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37 /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/utils /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/utils /Users/jiajin/Desktop/NMS/project/NMS_Project_NS3/ns-allinone-3.37/ns-3.37/cmake-cache/utils/CMakeFiles/test-runner.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : utils/CMakeFiles/test-runner.dir/depend

