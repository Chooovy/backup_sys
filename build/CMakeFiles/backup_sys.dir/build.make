# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/marcus/backup_sys

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/marcus/backup_sys/build

# Include any dependencies generated for this target.
include CMakeFiles/backup_sys.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/backup_sys.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/backup_sys.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/backup_sys.dir/flags.make

CMakeFiles/backup_sys.dir/src/compress.cpp.o: CMakeFiles/backup_sys.dir/flags.make
CMakeFiles/backup_sys.dir/src/compress.cpp.o: ../src/compress.cpp
CMakeFiles/backup_sys.dir/src/compress.cpp.o: CMakeFiles/backup_sys.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/marcus/backup_sys/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/backup_sys.dir/src/compress.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/backup_sys.dir/src/compress.cpp.o -MF CMakeFiles/backup_sys.dir/src/compress.cpp.o.d -o CMakeFiles/backup_sys.dir/src/compress.cpp.o -c /home/marcus/backup_sys/src/compress.cpp

CMakeFiles/backup_sys.dir/src/compress.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/backup_sys.dir/src/compress.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/marcus/backup_sys/src/compress.cpp > CMakeFiles/backup_sys.dir/src/compress.cpp.i

CMakeFiles/backup_sys.dir/src/compress.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/backup_sys.dir/src/compress.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/marcus/backup_sys/src/compress.cpp -o CMakeFiles/backup_sys.dir/src/compress.cpp.s

CMakeFiles/backup_sys.dir/src/do.cpp.o: CMakeFiles/backup_sys.dir/flags.make
CMakeFiles/backup_sys.dir/src/do.cpp.o: ../src/do.cpp
CMakeFiles/backup_sys.dir/src/do.cpp.o: CMakeFiles/backup_sys.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/marcus/backup_sys/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/backup_sys.dir/src/do.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/backup_sys.dir/src/do.cpp.o -MF CMakeFiles/backup_sys.dir/src/do.cpp.o.d -o CMakeFiles/backup_sys.dir/src/do.cpp.o -c /home/marcus/backup_sys/src/do.cpp

CMakeFiles/backup_sys.dir/src/do.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/backup_sys.dir/src/do.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/marcus/backup_sys/src/do.cpp > CMakeFiles/backup_sys.dir/src/do.cpp.i

CMakeFiles/backup_sys.dir/src/do.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/backup_sys.dir/src/do.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/marcus/backup_sys/src/do.cpp -o CMakeFiles/backup_sys.dir/src/do.cpp.s

CMakeFiles/backup_sys.dir/src/encrypt.cpp.o: CMakeFiles/backup_sys.dir/flags.make
CMakeFiles/backup_sys.dir/src/encrypt.cpp.o: ../src/encrypt.cpp
CMakeFiles/backup_sys.dir/src/encrypt.cpp.o: CMakeFiles/backup_sys.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/marcus/backup_sys/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/backup_sys.dir/src/encrypt.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/backup_sys.dir/src/encrypt.cpp.o -MF CMakeFiles/backup_sys.dir/src/encrypt.cpp.o.d -o CMakeFiles/backup_sys.dir/src/encrypt.cpp.o -c /home/marcus/backup_sys/src/encrypt.cpp

CMakeFiles/backup_sys.dir/src/encrypt.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/backup_sys.dir/src/encrypt.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/marcus/backup_sys/src/encrypt.cpp > CMakeFiles/backup_sys.dir/src/encrypt.cpp.i

CMakeFiles/backup_sys.dir/src/encrypt.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/backup_sys.dir/src/encrypt.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/marcus/backup_sys/src/encrypt.cpp -o CMakeFiles/backup_sys.dir/src/encrypt.cpp.s

CMakeFiles/backup_sys.dir/src/main.cpp.o: CMakeFiles/backup_sys.dir/flags.make
CMakeFiles/backup_sys.dir/src/main.cpp.o: ../src/main.cpp
CMakeFiles/backup_sys.dir/src/main.cpp.o: CMakeFiles/backup_sys.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/marcus/backup_sys/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/backup_sys.dir/src/main.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/backup_sys.dir/src/main.cpp.o -MF CMakeFiles/backup_sys.dir/src/main.cpp.o.d -o CMakeFiles/backup_sys.dir/src/main.cpp.o -c /home/marcus/backup_sys/src/main.cpp

CMakeFiles/backup_sys.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/backup_sys.dir/src/main.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/marcus/backup_sys/src/main.cpp > CMakeFiles/backup_sys.dir/src/main.cpp.i

CMakeFiles/backup_sys.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/backup_sys.dir/src/main.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/marcus/backup_sys/src/main.cpp -o CMakeFiles/backup_sys.dir/src/main.cpp.s

CMakeFiles/backup_sys.dir/src/tar.cpp.o: CMakeFiles/backup_sys.dir/flags.make
CMakeFiles/backup_sys.dir/src/tar.cpp.o: ../src/tar.cpp
CMakeFiles/backup_sys.dir/src/tar.cpp.o: CMakeFiles/backup_sys.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/marcus/backup_sys/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/backup_sys.dir/src/tar.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/backup_sys.dir/src/tar.cpp.o -MF CMakeFiles/backup_sys.dir/src/tar.cpp.o.d -o CMakeFiles/backup_sys.dir/src/tar.cpp.o -c /home/marcus/backup_sys/src/tar.cpp

CMakeFiles/backup_sys.dir/src/tar.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/backup_sys.dir/src/tar.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/marcus/backup_sys/src/tar.cpp > CMakeFiles/backup_sys.dir/src/tar.cpp.i

CMakeFiles/backup_sys.dir/src/tar.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/backup_sys.dir/src/tar.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/marcus/backup_sys/src/tar.cpp -o CMakeFiles/backup_sys.dir/src/tar.cpp.s

# Object files for target backup_sys
backup_sys_OBJECTS = \
"CMakeFiles/backup_sys.dir/src/compress.cpp.o" \
"CMakeFiles/backup_sys.dir/src/do.cpp.o" \
"CMakeFiles/backup_sys.dir/src/encrypt.cpp.o" \
"CMakeFiles/backup_sys.dir/src/main.cpp.o" \
"CMakeFiles/backup_sys.dir/src/tar.cpp.o"

# External object files for target backup_sys
backup_sys_EXTERNAL_OBJECTS =

backup_sys: CMakeFiles/backup_sys.dir/src/compress.cpp.o
backup_sys: CMakeFiles/backup_sys.dir/src/do.cpp.o
backup_sys: CMakeFiles/backup_sys.dir/src/encrypt.cpp.o
backup_sys: CMakeFiles/backup_sys.dir/src/main.cpp.o
backup_sys: CMakeFiles/backup_sys.dir/src/tar.cpp.o
backup_sys: CMakeFiles/backup_sys.dir/build.make
backup_sys: /usr/lib/x86_64-linux-gnu/libcrypto.a
backup_sys: CMakeFiles/backup_sys.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/marcus/backup_sys/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable backup_sys"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/backup_sys.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/backup_sys.dir/build: backup_sys
.PHONY : CMakeFiles/backup_sys.dir/build

CMakeFiles/backup_sys.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/backup_sys.dir/cmake_clean.cmake
.PHONY : CMakeFiles/backup_sys.dir/clean

CMakeFiles/backup_sys.dir/depend:
	cd /home/marcus/backup_sys/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/marcus/backup_sys /home/marcus/backup_sys /home/marcus/backup_sys/build /home/marcus/backup_sys/build /home/marcus/backup_sys/build/CMakeFiles/backup_sys.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/backup_sys.dir/depend

