# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/hj/work/dem/Delaunay_pic

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/hj/work/dem/build-Delaunay_pic-Desktop-Default

# Include any dependencies generated for this target.
include CMakeFiles/Delaunay_pic.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Delaunay_pic.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Delaunay_pic.dir/flags.make

CMakeFiles/Delaunay_pic.dir/src/test/Delaunay_pic.cpp.o: CMakeFiles/Delaunay_pic.dir/flags.make
CMakeFiles/Delaunay_pic.dir/src/test/Delaunay_pic.cpp.o: /home/hj/work/dem/Delaunay_pic/src/test/Delaunay_pic.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hj/work/dem/build-Delaunay_pic-Desktop-Default/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Delaunay_pic.dir/src/test/Delaunay_pic.cpp.o"
	/usr/bin/g++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Delaunay_pic.dir/src/test/Delaunay_pic.cpp.o -c /home/hj/work/dem/Delaunay_pic/src/test/Delaunay_pic.cpp

CMakeFiles/Delaunay_pic.dir/src/test/Delaunay_pic.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Delaunay_pic.dir/src/test/Delaunay_pic.cpp.i"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hj/work/dem/Delaunay_pic/src/test/Delaunay_pic.cpp > CMakeFiles/Delaunay_pic.dir/src/test/Delaunay_pic.cpp.i

CMakeFiles/Delaunay_pic.dir/src/test/Delaunay_pic.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Delaunay_pic.dir/src/test/Delaunay_pic.cpp.s"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hj/work/dem/Delaunay_pic/src/test/Delaunay_pic.cpp -o CMakeFiles/Delaunay_pic.dir/src/test/Delaunay_pic.cpp.s

CMakeFiles/Delaunay_pic.dir/src/test/Delaunay_pic.cpp.o.requires:

.PHONY : CMakeFiles/Delaunay_pic.dir/src/test/Delaunay_pic.cpp.o.requires

CMakeFiles/Delaunay_pic.dir/src/test/Delaunay_pic.cpp.o.provides: CMakeFiles/Delaunay_pic.dir/src/test/Delaunay_pic.cpp.o.requires
	$(MAKE) -f CMakeFiles/Delaunay_pic.dir/build.make CMakeFiles/Delaunay_pic.dir/src/test/Delaunay_pic.cpp.o.provides.build
.PHONY : CMakeFiles/Delaunay_pic.dir/src/test/Delaunay_pic.cpp.o.provides

CMakeFiles/Delaunay_pic.dir/src/test/Delaunay_pic.cpp.o.provides.build: CMakeFiles/Delaunay_pic.dir/src/test/Delaunay_pic.cpp.o


CMakeFiles/Delaunay_pic.dir/src/mesher/Triangler.cpp.o: CMakeFiles/Delaunay_pic.dir/flags.make
CMakeFiles/Delaunay_pic.dir/src/mesher/Triangler.cpp.o: /home/hj/work/dem/Delaunay_pic/src/mesher/Triangler.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hj/work/dem/build-Delaunay_pic-Desktop-Default/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Delaunay_pic.dir/src/mesher/Triangler.cpp.o"
	/usr/bin/g++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Delaunay_pic.dir/src/mesher/Triangler.cpp.o -c /home/hj/work/dem/Delaunay_pic/src/mesher/Triangler.cpp

CMakeFiles/Delaunay_pic.dir/src/mesher/Triangler.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Delaunay_pic.dir/src/mesher/Triangler.cpp.i"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hj/work/dem/Delaunay_pic/src/mesher/Triangler.cpp > CMakeFiles/Delaunay_pic.dir/src/mesher/Triangler.cpp.i

CMakeFiles/Delaunay_pic.dir/src/mesher/Triangler.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Delaunay_pic.dir/src/mesher/Triangler.cpp.s"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hj/work/dem/Delaunay_pic/src/mesher/Triangler.cpp -o CMakeFiles/Delaunay_pic.dir/src/mesher/Triangler.cpp.s

CMakeFiles/Delaunay_pic.dir/src/mesher/Triangler.cpp.o.requires:

.PHONY : CMakeFiles/Delaunay_pic.dir/src/mesher/Triangler.cpp.o.requires

CMakeFiles/Delaunay_pic.dir/src/mesher/Triangler.cpp.o.provides: CMakeFiles/Delaunay_pic.dir/src/mesher/Triangler.cpp.o.requires
	$(MAKE) -f CMakeFiles/Delaunay_pic.dir/build.make CMakeFiles/Delaunay_pic.dir/src/mesher/Triangler.cpp.o.provides.build
.PHONY : CMakeFiles/Delaunay_pic.dir/src/mesher/Triangler.cpp.o.provides

CMakeFiles/Delaunay_pic.dir/src/mesher/Triangler.cpp.o.provides.build: CMakeFiles/Delaunay_pic.dir/src/mesher/Triangler.cpp.o


CMakeFiles/Delaunay_pic.dir/src/display/Display.cpp.o: CMakeFiles/Delaunay_pic.dir/flags.make
CMakeFiles/Delaunay_pic.dir/src/display/Display.cpp.o: /home/hj/work/dem/Delaunay_pic/src/display/Display.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hj/work/dem/build-Delaunay_pic-Desktop-Default/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Delaunay_pic.dir/src/display/Display.cpp.o"
	/usr/bin/g++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Delaunay_pic.dir/src/display/Display.cpp.o -c /home/hj/work/dem/Delaunay_pic/src/display/Display.cpp

CMakeFiles/Delaunay_pic.dir/src/display/Display.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Delaunay_pic.dir/src/display/Display.cpp.i"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hj/work/dem/Delaunay_pic/src/display/Display.cpp > CMakeFiles/Delaunay_pic.dir/src/display/Display.cpp.i

CMakeFiles/Delaunay_pic.dir/src/display/Display.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Delaunay_pic.dir/src/display/Display.cpp.s"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hj/work/dem/Delaunay_pic/src/display/Display.cpp -o CMakeFiles/Delaunay_pic.dir/src/display/Display.cpp.s

CMakeFiles/Delaunay_pic.dir/src/display/Display.cpp.o.requires:

.PHONY : CMakeFiles/Delaunay_pic.dir/src/display/Display.cpp.o.requires

CMakeFiles/Delaunay_pic.dir/src/display/Display.cpp.o.provides: CMakeFiles/Delaunay_pic.dir/src/display/Display.cpp.o.requires
	$(MAKE) -f CMakeFiles/Delaunay_pic.dir/build.make CMakeFiles/Delaunay_pic.dir/src/display/Display.cpp.o.provides.build
.PHONY : CMakeFiles/Delaunay_pic.dir/src/display/Display.cpp.o.provides

CMakeFiles/Delaunay_pic.dir/src/display/Display.cpp.o.provides.build: CMakeFiles/Delaunay_pic.dir/src/display/Display.cpp.o


CMakeFiles/Delaunay_pic.dir/src/display/Dem_qgl.cpp.o: CMakeFiles/Delaunay_pic.dir/flags.make
CMakeFiles/Delaunay_pic.dir/src/display/Dem_qgl.cpp.o: /home/hj/work/dem/Delaunay_pic/src/display/Dem_qgl.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hj/work/dem/build-Delaunay_pic-Desktop-Default/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/Delaunay_pic.dir/src/display/Dem_qgl.cpp.o"
	/usr/bin/g++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Delaunay_pic.dir/src/display/Dem_qgl.cpp.o -c /home/hj/work/dem/Delaunay_pic/src/display/Dem_qgl.cpp

CMakeFiles/Delaunay_pic.dir/src/display/Dem_qgl.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Delaunay_pic.dir/src/display/Dem_qgl.cpp.i"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hj/work/dem/Delaunay_pic/src/display/Dem_qgl.cpp > CMakeFiles/Delaunay_pic.dir/src/display/Dem_qgl.cpp.i

CMakeFiles/Delaunay_pic.dir/src/display/Dem_qgl.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Delaunay_pic.dir/src/display/Dem_qgl.cpp.s"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hj/work/dem/Delaunay_pic/src/display/Dem_qgl.cpp -o CMakeFiles/Delaunay_pic.dir/src/display/Dem_qgl.cpp.s

CMakeFiles/Delaunay_pic.dir/src/display/Dem_qgl.cpp.o.requires:

.PHONY : CMakeFiles/Delaunay_pic.dir/src/display/Dem_qgl.cpp.o.requires

CMakeFiles/Delaunay_pic.dir/src/display/Dem_qgl.cpp.o.provides: CMakeFiles/Delaunay_pic.dir/src/display/Dem_qgl.cpp.o.requires
	$(MAKE) -f CMakeFiles/Delaunay_pic.dir/build.make CMakeFiles/Delaunay_pic.dir/src/display/Dem_qgl.cpp.o.provides.build
.PHONY : CMakeFiles/Delaunay_pic.dir/src/display/Dem_qgl.cpp.o.provides

CMakeFiles/Delaunay_pic.dir/src/display/Dem_qgl.cpp.o.provides.build: CMakeFiles/Delaunay_pic.dir/src/display/Dem_qgl.cpp.o


CMakeFiles/Delaunay_pic.dir/src/display/Display_qgl.cpp.o: CMakeFiles/Delaunay_pic.dir/flags.make
CMakeFiles/Delaunay_pic.dir/src/display/Display_qgl.cpp.o: /home/hj/work/dem/Delaunay_pic/src/display/Display_qgl.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hj/work/dem/build-Delaunay_pic-Desktop-Default/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/Delaunay_pic.dir/src/display/Display_qgl.cpp.o"
	/usr/bin/g++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Delaunay_pic.dir/src/display/Display_qgl.cpp.o -c /home/hj/work/dem/Delaunay_pic/src/display/Display_qgl.cpp

CMakeFiles/Delaunay_pic.dir/src/display/Display_qgl.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Delaunay_pic.dir/src/display/Display_qgl.cpp.i"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hj/work/dem/Delaunay_pic/src/display/Display_qgl.cpp > CMakeFiles/Delaunay_pic.dir/src/display/Display_qgl.cpp.i

CMakeFiles/Delaunay_pic.dir/src/display/Display_qgl.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Delaunay_pic.dir/src/display/Display_qgl.cpp.s"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hj/work/dem/Delaunay_pic/src/display/Display_qgl.cpp -o CMakeFiles/Delaunay_pic.dir/src/display/Display_qgl.cpp.s

CMakeFiles/Delaunay_pic.dir/src/display/Display_qgl.cpp.o.requires:

.PHONY : CMakeFiles/Delaunay_pic.dir/src/display/Display_qgl.cpp.o.requires

CMakeFiles/Delaunay_pic.dir/src/display/Display_qgl.cpp.o.provides: CMakeFiles/Delaunay_pic.dir/src/display/Display_qgl.cpp.o.requires
	$(MAKE) -f CMakeFiles/Delaunay_pic.dir/build.make CMakeFiles/Delaunay_pic.dir/src/display/Display_qgl.cpp.o.provides.build
.PHONY : CMakeFiles/Delaunay_pic.dir/src/display/Display_qgl.cpp.o.provides

CMakeFiles/Delaunay_pic.dir/src/display/Display_qgl.cpp.o.provides.build: CMakeFiles/Delaunay_pic.dir/src/display/Display_qgl.cpp.o


CMakeFiles/Delaunay_pic.dir/src/points/Points_filter.cpp.o: CMakeFiles/Delaunay_pic.dir/flags.make
CMakeFiles/Delaunay_pic.dir/src/points/Points_filter.cpp.o: /home/hj/work/dem/Delaunay_pic/src/points/Points_filter.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hj/work/dem/build-Delaunay_pic-Desktop-Default/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/Delaunay_pic.dir/src/points/Points_filter.cpp.o"
	/usr/bin/g++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Delaunay_pic.dir/src/points/Points_filter.cpp.o -c /home/hj/work/dem/Delaunay_pic/src/points/Points_filter.cpp

CMakeFiles/Delaunay_pic.dir/src/points/Points_filter.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Delaunay_pic.dir/src/points/Points_filter.cpp.i"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hj/work/dem/Delaunay_pic/src/points/Points_filter.cpp > CMakeFiles/Delaunay_pic.dir/src/points/Points_filter.cpp.i

CMakeFiles/Delaunay_pic.dir/src/points/Points_filter.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Delaunay_pic.dir/src/points/Points_filter.cpp.s"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hj/work/dem/Delaunay_pic/src/points/Points_filter.cpp -o CMakeFiles/Delaunay_pic.dir/src/points/Points_filter.cpp.s

CMakeFiles/Delaunay_pic.dir/src/points/Points_filter.cpp.o.requires:

.PHONY : CMakeFiles/Delaunay_pic.dir/src/points/Points_filter.cpp.o.requires

CMakeFiles/Delaunay_pic.dir/src/points/Points_filter.cpp.o.provides: CMakeFiles/Delaunay_pic.dir/src/points/Points_filter.cpp.o.requires
	$(MAKE) -f CMakeFiles/Delaunay_pic.dir/build.make CMakeFiles/Delaunay_pic.dir/src/points/Points_filter.cpp.o.provides.build
.PHONY : CMakeFiles/Delaunay_pic.dir/src/points/Points_filter.cpp.o.provides

CMakeFiles/Delaunay_pic.dir/src/points/Points_filter.cpp.o.provides.build: CMakeFiles/Delaunay_pic.dir/src/points/Points_filter.cpp.o


CMakeFiles/Delaunay_pic.dir/src/struct_class/Struct_Class.cpp.o: CMakeFiles/Delaunay_pic.dir/flags.make
CMakeFiles/Delaunay_pic.dir/src/struct_class/Struct_Class.cpp.o: /home/hj/work/dem/Delaunay_pic/src/struct_class/Struct_Class.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hj/work/dem/build-Delaunay_pic-Desktop-Default/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/Delaunay_pic.dir/src/struct_class/Struct_Class.cpp.o"
	/usr/bin/g++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Delaunay_pic.dir/src/struct_class/Struct_Class.cpp.o -c /home/hj/work/dem/Delaunay_pic/src/struct_class/Struct_Class.cpp

CMakeFiles/Delaunay_pic.dir/src/struct_class/Struct_Class.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Delaunay_pic.dir/src/struct_class/Struct_Class.cpp.i"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hj/work/dem/Delaunay_pic/src/struct_class/Struct_Class.cpp > CMakeFiles/Delaunay_pic.dir/src/struct_class/Struct_Class.cpp.i

CMakeFiles/Delaunay_pic.dir/src/struct_class/Struct_Class.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Delaunay_pic.dir/src/struct_class/Struct_Class.cpp.s"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hj/work/dem/Delaunay_pic/src/struct_class/Struct_Class.cpp -o CMakeFiles/Delaunay_pic.dir/src/struct_class/Struct_Class.cpp.s

CMakeFiles/Delaunay_pic.dir/src/struct_class/Struct_Class.cpp.o.requires:

.PHONY : CMakeFiles/Delaunay_pic.dir/src/struct_class/Struct_Class.cpp.o.requires

CMakeFiles/Delaunay_pic.dir/src/struct_class/Struct_Class.cpp.o.provides: CMakeFiles/Delaunay_pic.dir/src/struct_class/Struct_Class.cpp.o.requires
	$(MAKE) -f CMakeFiles/Delaunay_pic.dir/build.make CMakeFiles/Delaunay_pic.dir/src/struct_class/Struct_Class.cpp.o.provides.build
.PHONY : CMakeFiles/Delaunay_pic.dir/src/struct_class/Struct_Class.cpp.o.provides

CMakeFiles/Delaunay_pic.dir/src/struct_class/Struct_Class.cpp.o.provides.build: CMakeFiles/Delaunay_pic.dir/src/struct_class/Struct_Class.cpp.o


CMakeFiles/Delaunay_pic.dir/src/tile/Tile.cpp.o: CMakeFiles/Delaunay_pic.dir/flags.make
CMakeFiles/Delaunay_pic.dir/src/tile/Tile.cpp.o: /home/hj/work/dem/Delaunay_pic/src/tile/Tile.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hj/work/dem/build-Delaunay_pic-Desktop-Default/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/Delaunay_pic.dir/src/tile/Tile.cpp.o"
	/usr/bin/g++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Delaunay_pic.dir/src/tile/Tile.cpp.o -c /home/hj/work/dem/Delaunay_pic/src/tile/Tile.cpp

CMakeFiles/Delaunay_pic.dir/src/tile/Tile.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Delaunay_pic.dir/src/tile/Tile.cpp.i"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hj/work/dem/Delaunay_pic/src/tile/Tile.cpp > CMakeFiles/Delaunay_pic.dir/src/tile/Tile.cpp.i

CMakeFiles/Delaunay_pic.dir/src/tile/Tile.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Delaunay_pic.dir/src/tile/Tile.cpp.s"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hj/work/dem/Delaunay_pic/src/tile/Tile.cpp -o CMakeFiles/Delaunay_pic.dir/src/tile/Tile.cpp.s

CMakeFiles/Delaunay_pic.dir/src/tile/Tile.cpp.o.requires:

.PHONY : CMakeFiles/Delaunay_pic.dir/src/tile/Tile.cpp.o.requires

CMakeFiles/Delaunay_pic.dir/src/tile/Tile.cpp.o.provides: CMakeFiles/Delaunay_pic.dir/src/tile/Tile.cpp.o.requires
	$(MAKE) -f CMakeFiles/Delaunay_pic.dir/build.make CMakeFiles/Delaunay_pic.dir/src/tile/Tile.cpp.o.provides.build
.PHONY : CMakeFiles/Delaunay_pic.dir/src/tile/Tile.cpp.o.provides

CMakeFiles/Delaunay_pic.dir/src/tile/Tile.cpp.o.provides.build: CMakeFiles/Delaunay_pic.dir/src/tile/Tile.cpp.o


# Object files for target Delaunay_pic
Delaunay_pic_OBJECTS = \
"CMakeFiles/Delaunay_pic.dir/src/test/Delaunay_pic.cpp.o" \
"CMakeFiles/Delaunay_pic.dir/src/mesher/Triangler.cpp.o" \
"CMakeFiles/Delaunay_pic.dir/src/display/Display.cpp.o" \
"CMakeFiles/Delaunay_pic.dir/src/display/Dem_qgl.cpp.o" \
"CMakeFiles/Delaunay_pic.dir/src/display/Display_qgl.cpp.o" \
"CMakeFiles/Delaunay_pic.dir/src/points/Points_filter.cpp.o" \
"CMakeFiles/Delaunay_pic.dir/src/struct_class/Struct_Class.cpp.o" \
"CMakeFiles/Delaunay_pic.dir/src/tile/Tile.cpp.o"

# External object files for target Delaunay_pic
Delaunay_pic_EXTERNAL_OBJECTS =

Delaunay_pic: CMakeFiles/Delaunay_pic.dir/src/test/Delaunay_pic.cpp.o
Delaunay_pic: CMakeFiles/Delaunay_pic.dir/src/mesher/Triangler.cpp.o
Delaunay_pic: CMakeFiles/Delaunay_pic.dir/src/display/Display.cpp.o
Delaunay_pic: CMakeFiles/Delaunay_pic.dir/src/display/Dem_qgl.cpp.o
Delaunay_pic: CMakeFiles/Delaunay_pic.dir/src/display/Display_qgl.cpp.o
Delaunay_pic: CMakeFiles/Delaunay_pic.dir/src/points/Points_filter.cpp.o
Delaunay_pic: CMakeFiles/Delaunay_pic.dir/src/struct_class/Struct_Class.cpp.o
Delaunay_pic: CMakeFiles/Delaunay_pic.dir/src/tile/Tile.cpp.o
Delaunay_pic: CMakeFiles/Delaunay_pic.dir/build.make
Delaunay_pic: /usr/lib/x86_64-linux-gnu/libmpfr.so
Delaunay_pic: /usr/lib/x86_64-linux-gnu/libgmp.so
Delaunay_pic: /usr/lib/libCGAL.so
Delaunay_pic: /usr/lib/x86_64-linux-gnu/libboost_thread.so
Delaunay_pic: /usr/lib/x86_64-linux-gnu/libboost_system.so
Delaunay_pic: /usr/lib/x86_64-linux-gnu/libpthread.so
Delaunay_pic: /usr/lib/x86_64-linux-gnu/libQtOpenGL.so
Delaunay_pic: /usr/lib/x86_64-linux-gnu/libQtGui.so
Delaunay_pic: /usr/lib/x86_64-linux-gnu/libQtXml.so
Delaunay_pic: /usr/lib/x86_64-linux-gnu/libQtCore.so
Delaunay_pic: /usr/lib/libCGAL.so
Delaunay_pic: /usr/local/lib/libopencv_highgui.so
Delaunay_pic: /usr/local/lib/libopencv_calib3d.so
Delaunay_pic: /usr/local/lib/libopencv_features2d.so
Delaunay_pic: /usr/local/lib/libopencv_legacy.so
Delaunay_pic: /usr/local/lib/libopencv_superres.so
Delaunay_pic: /usr/local/lib/libopencv_videostab.so
Delaunay_pic: /usr/local/lib/libopencv_ml.so
Delaunay_pic: /usr/local/lib/libopencv_contrib.so
Delaunay_pic: /usr/local/lib/libopencv_flann.so
Delaunay_pic: /usr/local/lib/libopencv_photo.so
Delaunay_pic: /usr/local/lib/libopencv_objdetect.so
Delaunay_pic: /usr/local/lib/libopencv_stitching.so
Delaunay_pic: /usr/local/lib/libopencv_imgproc.so
Delaunay_pic: /usr/local/lib/libopencv_ocl.so
Delaunay_pic: /usr/local/lib/libopencv_gpu.so
Delaunay_pic: /usr/local/lib/libopencv_core.so
Delaunay_pic: /usr/lib/x86_64-linux-gnu/libIlmImf.so
Delaunay_pic: /usr/lib/x86_64-linux-gnu/libglog.so
Delaunay_pic: /usr/lib/x86_64-linux-gnu/libGL.so
Delaunay_pic: /usr/lib/x86_64-linux-gnu/libGLU.so
Delaunay_pic: /usr/lib/x86_64-linux-gnu/libQGLViewer.so.2.5
Delaunay_pic: /usr/lib/x86_64-linux-gnu/libboost_thread.so
Delaunay_pic: /usr/lib/x86_64-linux-gnu/libboost_system.so
Delaunay_pic: /usr/lib/x86_64-linux-gnu/libpthread.so
Delaunay_pic: /usr/lib/x86_64-linux-gnu/libQtOpenGL.so
Delaunay_pic: /usr/lib/x86_64-linux-gnu/libQtGui.so
Delaunay_pic: /usr/lib/x86_64-linux-gnu/libQtXml.so
Delaunay_pic: /usr/lib/x86_64-linux-gnu/libQtCore.so
Delaunay_pic: /usr/local/lib/libopencv_highgui.so
Delaunay_pic: /usr/local/lib/libopencv_calib3d.so
Delaunay_pic: /usr/local/lib/libopencv_features2d.so
Delaunay_pic: /usr/local/lib/libopencv_legacy.so
Delaunay_pic: /usr/local/lib/libopencv_superres.so
Delaunay_pic: /usr/local/lib/libopencv_videostab.so
Delaunay_pic: /usr/local/lib/libopencv_ml.so
Delaunay_pic: /usr/local/lib/libopencv_contrib.so
Delaunay_pic: /usr/local/lib/libopencv_flann.so
Delaunay_pic: /usr/local/lib/libopencv_photo.so
Delaunay_pic: /usr/local/lib/libopencv_objdetect.so
Delaunay_pic: /usr/local/lib/libopencv_stitching.so
Delaunay_pic: /usr/local/lib/libopencv_imgproc.so
Delaunay_pic: /usr/local/lib/libopencv_ocl.so
Delaunay_pic: /usr/local/lib/libopencv_gpu.so
Delaunay_pic: /usr/local/lib/libopencv_core.so
Delaunay_pic: /usr/lib/x86_64-linux-gnu/libIlmImf.so
Delaunay_pic: /usr/lib/x86_64-linux-gnu/libglog.so
Delaunay_pic: /usr/lib/x86_64-linux-gnu/libGL.so
Delaunay_pic: /usr/lib/x86_64-linux-gnu/libGLU.so
Delaunay_pic: /usr/lib/x86_64-linux-gnu/libQGLViewer.so.2.5
Delaunay_pic: CMakeFiles/Delaunay_pic.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/hj/work/dem/build-Delaunay_pic-Desktop-Default/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Linking CXX executable Delaunay_pic"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Delaunay_pic.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Delaunay_pic.dir/build: Delaunay_pic

.PHONY : CMakeFiles/Delaunay_pic.dir/build

CMakeFiles/Delaunay_pic.dir/requires: CMakeFiles/Delaunay_pic.dir/src/test/Delaunay_pic.cpp.o.requires
CMakeFiles/Delaunay_pic.dir/requires: CMakeFiles/Delaunay_pic.dir/src/mesher/Triangler.cpp.o.requires
CMakeFiles/Delaunay_pic.dir/requires: CMakeFiles/Delaunay_pic.dir/src/display/Display.cpp.o.requires
CMakeFiles/Delaunay_pic.dir/requires: CMakeFiles/Delaunay_pic.dir/src/display/Dem_qgl.cpp.o.requires
CMakeFiles/Delaunay_pic.dir/requires: CMakeFiles/Delaunay_pic.dir/src/display/Display_qgl.cpp.o.requires
CMakeFiles/Delaunay_pic.dir/requires: CMakeFiles/Delaunay_pic.dir/src/points/Points_filter.cpp.o.requires
CMakeFiles/Delaunay_pic.dir/requires: CMakeFiles/Delaunay_pic.dir/src/struct_class/Struct_Class.cpp.o.requires
CMakeFiles/Delaunay_pic.dir/requires: CMakeFiles/Delaunay_pic.dir/src/tile/Tile.cpp.o.requires

.PHONY : CMakeFiles/Delaunay_pic.dir/requires

CMakeFiles/Delaunay_pic.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Delaunay_pic.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Delaunay_pic.dir/clean

CMakeFiles/Delaunay_pic.dir/depend:
	cd /home/hj/work/dem/build-Delaunay_pic-Desktop-Default && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/hj/work/dem/Delaunay_pic /home/hj/work/dem/Delaunay_pic /home/hj/work/dem/build-Delaunay_pic-Desktop-Default /home/hj/work/dem/build-Delaunay_pic-Desktop-Default /home/hj/work/dem/build-Delaunay_pic-Desktop-Default/CMakeFiles/Delaunay_pic.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Delaunay_pic.dir/depend

