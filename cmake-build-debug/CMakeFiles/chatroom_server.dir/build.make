# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.21

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
CMAKE_COMMAND = /home/canwaiting/tool/clion/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/canwaiting/tool/clion/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/canwaiting/cpp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/canwaiting/cpp/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/chatroom_server.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/chatroom_server.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/chatroom_server.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/chatroom_server.dir/flags.make

CMakeFiles/chatroom_server.dir/network-test/chatroom_server.cpp.o: CMakeFiles/chatroom_server.dir/flags.make
CMakeFiles/chatroom_server.dir/network-test/chatroom_server.cpp.o: ../network-test/chatroom_server.cpp
CMakeFiles/chatroom_server.dir/network-test/chatroom_server.cpp.o: CMakeFiles/chatroom_server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/canwaiting/cpp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/chatroom_server.dir/network-test/chatroom_server.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/chatroom_server.dir/network-test/chatroom_server.cpp.o -MF CMakeFiles/chatroom_server.dir/network-test/chatroom_server.cpp.o.d -o CMakeFiles/chatroom_server.dir/network-test/chatroom_server.cpp.o -c /home/canwaiting/cpp/network-test/chatroom_server.cpp

CMakeFiles/chatroom_server.dir/network-test/chatroom_server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/chatroom_server.dir/network-test/chatroom_server.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/canwaiting/cpp/network-test/chatroom_server.cpp > CMakeFiles/chatroom_server.dir/network-test/chatroom_server.cpp.i

CMakeFiles/chatroom_server.dir/network-test/chatroom_server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/chatroom_server.dir/network-test/chatroom_server.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/canwaiting/cpp/network-test/chatroom_server.cpp -o CMakeFiles/chatroom_server.dir/network-test/chatroom_server.cpp.s

# Object files for target chatroom_server
chatroom_server_OBJECTS = \
"CMakeFiles/chatroom_server.dir/network-test/chatroom_server.cpp.o"

# External object files for target chatroom_server
chatroom_server_EXTERNAL_OBJECTS =

chatroom_server: CMakeFiles/chatroom_server.dir/network-test/chatroom_server.cpp.o
chatroom_server: CMakeFiles/chatroom_server.dir/build.make
chatroom_server: CMakeFiles/chatroom_server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/canwaiting/cpp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable chatroom_server"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/chatroom_server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/chatroom_server.dir/build: chatroom_server
.PHONY : CMakeFiles/chatroom_server.dir/build

CMakeFiles/chatroom_server.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/chatroom_server.dir/cmake_clean.cmake
.PHONY : CMakeFiles/chatroom_server.dir/clean

CMakeFiles/chatroom_server.dir/depend:
	cd /home/canwaiting/cpp/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/canwaiting/cpp /home/canwaiting/cpp /home/canwaiting/cpp/cmake-build-debug /home/canwaiting/cpp/cmake-build-debug /home/canwaiting/cpp/cmake-build-debug/CMakeFiles/chatroom_server.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/chatroom_server.dir/depend
