# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /home/ricardo/Downloads/CLion-2018.1/clion-2018.1/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/ricardo/Downloads/CLion-2018.1/clion-2018.1/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ricardo/Universidade/CG2/TrabalhoPratico/Fase3/CG_TP

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ricardo/Universidade/CG2/TrabalhoPratico/Fase3/CG_TP/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/cg_tp.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/cg_tp.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/cg_tp.dir/flags.make

CMakeFiles/cg_tp.dir/main.cpp.o: CMakeFiles/cg_tp.dir/flags.make
CMakeFiles/cg_tp.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ricardo/Universidade/CG2/TrabalhoPratico/Fase3/CG_TP/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/cg_tp.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/cg_tp.dir/main.cpp.o -c /home/ricardo/Universidade/CG2/TrabalhoPratico/Fase3/CG_TP/main.cpp

CMakeFiles/cg_tp.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cg_tp.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ricardo/Universidade/CG2/TrabalhoPratico/Fase3/CG_TP/main.cpp > CMakeFiles/cg_tp.dir/main.cpp.i

CMakeFiles/cg_tp.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cg_tp.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ricardo/Universidade/CG2/TrabalhoPratico/Fase3/CG_TP/main.cpp -o CMakeFiles/cg_tp.dir/main.cpp.s

CMakeFiles/cg_tp.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/cg_tp.dir/main.cpp.o.requires

CMakeFiles/cg_tp.dir/main.cpp.o.provides: CMakeFiles/cg_tp.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/cg_tp.dir/build.make CMakeFiles/cg_tp.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/cg_tp.dir/main.cpp.o.provides

CMakeFiles/cg_tp.dir/main.cpp.o.provides.build: CMakeFiles/cg_tp.dir/main.cpp.o


CMakeFiles/cg_tp.dir/parser.cpp.o: CMakeFiles/cg_tp.dir/flags.make
CMakeFiles/cg_tp.dir/parser.cpp.o: ../parser.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ricardo/Universidade/CG2/TrabalhoPratico/Fase3/CG_TP/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/cg_tp.dir/parser.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/cg_tp.dir/parser.cpp.o -c /home/ricardo/Universidade/CG2/TrabalhoPratico/Fase3/CG_TP/parser.cpp

CMakeFiles/cg_tp.dir/parser.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cg_tp.dir/parser.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ricardo/Universidade/CG2/TrabalhoPratico/Fase3/CG_TP/parser.cpp > CMakeFiles/cg_tp.dir/parser.cpp.i

CMakeFiles/cg_tp.dir/parser.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cg_tp.dir/parser.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ricardo/Universidade/CG2/TrabalhoPratico/Fase3/CG_TP/parser.cpp -o CMakeFiles/cg_tp.dir/parser.cpp.s

CMakeFiles/cg_tp.dir/parser.cpp.o.requires:

.PHONY : CMakeFiles/cg_tp.dir/parser.cpp.o.requires

CMakeFiles/cg_tp.dir/parser.cpp.o.provides: CMakeFiles/cg_tp.dir/parser.cpp.o.requires
	$(MAKE) -f CMakeFiles/cg_tp.dir/build.make CMakeFiles/cg_tp.dir/parser.cpp.o.provides.build
.PHONY : CMakeFiles/cg_tp.dir/parser.cpp.o.provides

CMakeFiles/cg_tp.dir/parser.cpp.o.provides.build: CMakeFiles/cg_tp.dir/parser.cpp.o


CMakeFiles/cg_tp.dir/extractor.cpp.o: CMakeFiles/cg_tp.dir/flags.make
CMakeFiles/cg_tp.dir/extractor.cpp.o: ../extractor.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ricardo/Universidade/CG2/TrabalhoPratico/Fase3/CG_TP/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/cg_tp.dir/extractor.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/cg_tp.dir/extractor.cpp.o -c /home/ricardo/Universidade/CG2/TrabalhoPratico/Fase3/CG_TP/extractor.cpp

CMakeFiles/cg_tp.dir/extractor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cg_tp.dir/extractor.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ricardo/Universidade/CG2/TrabalhoPratico/Fase3/CG_TP/extractor.cpp > CMakeFiles/cg_tp.dir/extractor.cpp.i

CMakeFiles/cg_tp.dir/extractor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cg_tp.dir/extractor.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ricardo/Universidade/CG2/TrabalhoPratico/Fase3/CG_TP/extractor.cpp -o CMakeFiles/cg_tp.dir/extractor.cpp.s

CMakeFiles/cg_tp.dir/extractor.cpp.o.requires:

.PHONY : CMakeFiles/cg_tp.dir/extractor.cpp.o.requires

CMakeFiles/cg_tp.dir/extractor.cpp.o.provides: CMakeFiles/cg_tp.dir/extractor.cpp.o.requires
	$(MAKE) -f CMakeFiles/cg_tp.dir/build.make CMakeFiles/cg_tp.dir/extractor.cpp.o.provides.build
.PHONY : CMakeFiles/cg_tp.dir/extractor.cpp.o.provides

CMakeFiles/cg_tp.dir/extractor.cpp.o.provides.build: CMakeFiles/cg_tp.dir/extractor.cpp.o


CMakeFiles/cg_tp.dir/tinyxml2/tinyxml2.cpp.o: CMakeFiles/cg_tp.dir/flags.make
CMakeFiles/cg_tp.dir/tinyxml2/tinyxml2.cpp.o: ../tinyxml2/tinyxml2.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ricardo/Universidade/CG2/TrabalhoPratico/Fase3/CG_TP/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/cg_tp.dir/tinyxml2/tinyxml2.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/cg_tp.dir/tinyxml2/tinyxml2.cpp.o -c /home/ricardo/Universidade/CG2/TrabalhoPratico/Fase3/CG_TP/tinyxml2/tinyxml2.cpp

CMakeFiles/cg_tp.dir/tinyxml2/tinyxml2.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cg_tp.dir/tinyxml2/tinyxml2.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ricardo/Universidade/CG2/TrabalhoPratico/Fase3/CG_TP/tinyxml2/tinyxml2.cpp > CMakeFiles/cg_tp.dir/tinyxml2/tinyxml2.cpp.i

CMakeFiles/cg_tp.dir/tinyxml2/tinyxml2.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cg_tp.dir/tinyxml2/tinyxml2.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ricardo/Universidade/CG2/TrabalhoPratico/Fase3/CG_TP/tinyxml2/tinyxml2.cpp -o CMakeFiles/cg_tp.dir/tinyxml2/tinyxml2.cpp.s

CMakeFiles/cg_tp.dir/tinyxml2/tinyxml2.cpp.o.requires:

.PHONY : CMakeFiles/cg_tp.dir/tinyxml2/tinyxml2.cpp.o.requires

CMakeFiles/cg_tp.dir/tinyxml2/tinyxml2.cpp.o.provides: CMakeFiles/cg_tp.dir/tinyxml2/tinyxml2.cpp.o.requires
	$(MAKE) -f CMakeFiles/cg_tp.dir/build.make CMakeFiles/cg_tp.dir/tinyxml2/tinyxml2.cpp.o.provides.build
.PHONY : CMakeFiles/cg_tp.dir/tinyxml2/tinyxml2.cpp.o.provides

CMakeFiles/cg_tp.dir/tinyxml2/tinyxml2.cpp.o.provides.build: CMakeFiles/cg_tp.dir/tinyxml2/tinyxml2.cpp.o


# Object files for target cg_tp
cg_tp_OBJECTS = \
"CMakeFiles/cg_tp.dir/main.cpp.o" \
"CMakeFiles/cg_tp.dir/parser.cpp.o" \
"CMakeFiles/cg_tp.dir/extractor.cpp.o" \
"CMakeFiles/cg_tp.dir/tinyxml2/tinyxml2.cpp.o"

# External object files for target cg_tp
cg_tp_EXTERNAL_OBJECTS =

cg_tp: CMakeFiles/cg_tp.dir/main.cpp.o
cg_tp: CMakeFiles/cg_tp.dir/parser.cpp.o
cg_tp: CMakeFiles/cg_tp.dir/extractor.cpp.o
cg_tp: CMakeFiles/cg_tp.dir/tinyxml2/tinyxml2.cpp.o
cg_tp: CMakeFiles/cg_tp.dir/build.make
cg_tp: /usr/lib64/libGLEW.so
cg_tp: /usr/lib64/libGL.so
cg_tp: /usr/lib64/libGLU.so
cg_tp: /usr/lib64/libglut.so
cg_tp: /usr/lib64/libXmu.so
cg_tp: /usr/lib64/libXi.so
cg_tp: CMakeFiles/cg_tp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ricardo/Universidade/CG2/TrabalhoPratico/Fase3/CG_TP/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable cg_tp"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cg_tp.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/cg_tp.dir/build: cg_tp

.PHONY : CMakeFiles/cg_tp.dir/build

CMakeFiles/cg_tp.dir/requires: CMakeFiles/cg_tp.dir/main.cpp.o.requires
CMakeFiles/cg_tp.dir/requires: CMakeFiles/cg_tp.dir/parser.cpp.o.requires
CMakeFiles/cg_tp.dir/requires: CMakeFiles/cg_tp.dir/extractor.cpp.o.requires
CMakeFiles/cg_tp.dir/requires: CMakeFiles/cg_tp.dir/tinyxml2/tinyxml2.cpp.o.requires

.PHONY : CMakeFiles/cg_tp.dir/requires

CMakeFiles/cg_tp.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/cg_tp.dir/cmake_clean.cmake
.PHONY : CMakeFiles/cg_tp.dir/clean

CMakeFiles/cg_tp.dir/depend:
	cd /home/ricardo/Universidade/CG2/TrabalhoPratico/Fase3/CG_TP/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ricardo/Universidade/CG2/TrabalhoPratico/Fase3/CG_TP /home/ricardo/Universidade/CG2/TrabalhoPratico/Fase3/CG_TP /home/ricardo/Universidade/CG2/TrabalhoPratico/Fase3/CG_TP/cmake-build-debug /home/ricardo/Universidade/CG2/TrabalhoPratico/Fase3/CG_TP/cmake-build-debug /home/ricardo/Universidade/CG2/TrabalhoPratico/Fase3/CG_TP/cmake-build-debug/CMakeFiles/cg_tp.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/cg_tp.dir/depend

