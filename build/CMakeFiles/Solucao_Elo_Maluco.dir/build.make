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
CMAKE_SOURCE_DIR = /home/tobi/Elo_maluco

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/tobi/Elo_maluco/build

# Include any dependencies generated for this target.
include CMakeFiles/Solucao_Elo_Maluco.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Solucao_Elo_Maluco.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Solucao_Elo_Maluco.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Solucao_Elo_Maluco.dir/flags.make

CMakeFiles/Solucao_Elo_Maluco.dir/src/main.cpp.o: CMakeFiles/Solucao_Elo_Maluco.dir/flags.make
CMakeFiles/Solucao_Elo_Maluco.dir/src/main.cpp.o: ../src/main.cpp
CMakeFiles/Solucao_Elo_Maluco.dir/src/main.cpp.o: CMakeFiles/Solucao_Elo_Maluco.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tobi/Elo_maluco/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Solucao_Elo_Maluco.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Solucao_Elo_Maluco.dir/src/main.cpp.o -MF CMakeFiles/Solucao_Elo_Maluco.dir/src/main.cpp.o.d -o CMakeFiles/Solucao_Elo_Maluco.dir/src/main.cpp.o -c /home/tobi/Elo_maluco/src/main.cpp

CMakeFiles/Solucao_Elo_Maluco.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Solucao_Elo_Maluco.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tobi/Elo_maluco/src/main.cpp > CMakeFiles/Solucao_Elo_Maluco.dir/src/main.cpp.i

CMakeFiles/Solucao_Elo_Maluco.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Solucao_Elo_Maluco.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tobi/Elo_maluco/src/main.cpp -o CMakeFiles/Solucao_Elo_Maluco.dir/src/main.cpp.s

CMakeFiles/Solucao_Elo_Maluco.dir/src/application.cpp.o: CMakeFiles/Solucao_Elo_Maluco.dir/flags.make
CMakeFiles/Solucao_Elo_Maluco.dir/src/application.cpp.o: ../src/application.cpp
CMakeFiles/Solucao_Elo_Maluco.dir/src/application.cpp.o: CMakeFiles/Solucao_Elo_Maluco.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tobi/Elo_maluco/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Solucao_Elo_Maluco.dir/src/application.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Solucao_Elo_Maluco.dir/src/application.cpp.o -MF CMakeFiles/Solucao_Elo_Maluco.dir/src/application.cpp.o.d -o CMakeFiles/Solucao_Elo_Maluco.dir/src/application.cpp.o -c /home/tobi/Elo_maluco/src/application.cpp

CMakeFiles/Solucao_Elo_Maluco.dir/src/application.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Solucao_Elo_Maluco.dir/src/application.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tobi/Elo_maluco/src/application.cpp > CMakeFiles/Solucao_Elo_Maluco.dir/src/application.cpp.i

CMakeFiles/Solucao_Elo_Maluco.dir/src/application.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Solucao_Elo_Maluco.dir/src/application.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tobi/Elo_maluco/src/application.cpp -o CMakeFiles/Solucao_Elo_Maluco.dir/src/application.cpp.s

CMakeFiles/Solucao_Elo_Maluco.dir/src/tinyxml2.cpp.o: CMakeFiles/Solucao_Elo_Maluco.dir/flags.make
CMakeFiles/Solucao_Elo_Maluco.dir/src/tinyxml2.cpp.o: ../src/tinyxml2.cpp
CMakeFiles/Solucao_Elo_Maluco.dir/src/tinyxml2.cpp.o: CMakeFiles/Solucao_Elo_Maluco.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tobi/Elo_maluco/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Solucao_Elo_Maluco.dir/src/tinyxml2.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Solucao_Elo_Maluco.dir/src/tinyxml2.cpp.o -MF CMakeFiles/Solucao_Elo_Maluco.dir/src/tinyxml2.cpp.o.d -o CMakeFiles/Solucao_Elo_Maluco.dir/src/tinyxml2.cpp.o -c /home/tobi/Elo_maluco/src/tinyxml2.cpp

CMakeFiles/Solucao_Elo_Maluco.dir/src/tinyxml2.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Solucao_Elo_Maluco.dir/src/tinyxml2.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tobi/Elo_maluco/src/tinyxml2.cpp > CMakeFiles/Solucao_Elo_Maluco.dir/src/tinyxml2.cpp.i

CMakeFiles/Solucao_Elo_Maluco.dir/src/tinyxml2.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Solucao_Elo_Maluco.dir/src/tinyxml2.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tobi/Elo_maluco/src/tinyxml2.cpp -o CMakeFiles/Solucao_Elo_Maluco.dir/src/tinyxml2.cpp.s

# Object files for target Solucao_Elo_Maluco
Solucao_Elo_Maluco_OBJECTS = \
"CMakeFiles/Solucao_Elo_Maluco.dir/src/main.cpp.o" \
"CMakeFiles/Solucao_Elo_Maluco.dir/src/application.cpp.o" \
"CMakeFiles/Solucao_Elo_Maluco.dir/src/tinyxml2.cpp.o"

# External object files for target Solucao_Elo_Maluco
Solucao_Elo_Maluco_EXTERNAL_OBJECTS =

Solucao_Elo_Maluco: CMakeFiles/Solucao_Elo_Maluco.dir/src/main.cpp.o
Solucao_Elo_Maluco: CMakeFiles/Solucao_Elo_Maluco.dir/src/application.cpp.o
Solucao_Elo_Maluco: CMakeFiles/Solucao_Elo_Maluco.dir/src/tinyxml2.cpp.o
Solucao_Elo_Maluco: CMakeFiles/Solucao_Elo_Maluco.dir/build.make
Solucao_Elo_Maluco: CMakeFiles/Solucao_Elo_Maluco.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/tobi/Elo_maluco/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable Solucao_Elo_Maluco"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Solucao_Elo_Maluco.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Solucao_Elo_Maluco.dir/build: Solucao_Elo_Maluco
.PHONY : CMakeFiles/Solucao_Elo_Maluco.dir/build

CMakeFiles/Solucao_Elo_Maluco.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Solucao_Elo_Maluco.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Solucao_Elo_Maluco.dir/clean

CMakeFiles/Solucao_Elo_Maluco.dir/depend:
	cd /home/tobi/Elo_maluco/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tobi/Elo_maluco /home/tobi/Elo_maluco /home/tobi/Elo_maluco/build /home/tobi/Elo_maluco/build /home/tobi/Elo_maluco/build/CMakeFiles/Solucao_Elo_Maluco.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Solucao_Elo_Maluco.dir/depend

