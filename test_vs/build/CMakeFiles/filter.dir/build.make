# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.11

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.11.0/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.11.0/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/lmn/opencv_ws/test_vs

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/lmn/opencv_ws/test_vs/build

# Include any dependencies generated for this target.
include CMakeFiles/filter.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/filter.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/filter.dir/flags.make

CMakeFiles/filter.dir/src/filter.cpp.o: CMakeFiles/filter.dir/flags.make
CMakeFiles/filter.dir/src/filter.cpp.o: ../src/filter.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/lmn/opencv_ws/test_vs/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/filter.dir/src/filter.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/filter.dir/src/filter.cpp.o -c /Users/lmn/opencv_ws/test_vs/src/filter.cpp

CMakeFiles/filter.dir/src/filter.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/filter.dir/src/filter.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/lmn/opencv_ws/test_vs/src/filter.cpp > CMakeFiles/filter.dir/src/filter.cpp.i

CMakeFiles/filter.dir/src/filter.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/filter.dir/src/filter.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/lmn/opencv_ws/test_vs/src/filter.cpp -o CMakeFiles/filter.dir/src/filter.cpp.s

# Object files for target filter
filter_OBJECTS = \
"CMakeFiles/filter.dir/src/filter.cpp.o"

# External object files for target filter
filter_EXTERNAL_OBJECTS =

filter: CMakeFiles/filter.dir/src/filter.cpp.o
filter: CMakeFiles/filter.dir/build.make
filter: /Users/lmn/opencv-3.2.0/install/lib/libopencv_shape.3.2.0.dylib
filter: /Users/lmn/opencv-3.2.0/install/lib/libopencv_stitching.3.2.0.dylib
filter: /Users/lmn/opencv-3.2.0/install/lib/libopencv_superres.3.2.0.dylib
filter: /Users/lmn/opencv-3.2.0/install/lib/libopencv_videostab.3.2.0.dylib
filter: /Users/lmn/opencv-3.2.0/install/lib/libopencv_viz.3.2.0.dylib
filter: /Users/lmn/opencv-3.2.0/install/lib/libopencv_objdetect.3.2.0.dylib
filter: /Users/lmn/opencv-3.2.0/install/lib/libopencv_calib3d.3.2.0.dylib
filter: /Users/lmn/opencv-3.2.0/install/lib/libopencv_features2d.3.2.0.dylib
filter: /Users/lmn/opencv-3.2.0/install/lib/libopencv_flann.3.2.0.dylib
filter: /Users/lmn/opencv-3.2.0/install/lib/libopencv_highgui.3.2.0.dylib
filter: /Users/lmn/opencv-3.2.0/install/lib/libopencv_ml.3.2.0.dylib
filter: /Users/lmn/opencv-3.2.0/install/lib/libopencv_photo.3.2.0.dylib
filter: /Users/lmn/opencv-3.2.0/install/lib/libopencv_video.3.2.0.dylib
filter: /Users/lmn/opencv-3.2.0/install/lib/libopencv_videoio.3.2.0.dylib
filter: /Users/lmn/opencv-3.2.0/install/lib/libopencv_imgcodecs.3.2.0.dylib
filter: /Users/lmn/opencv-3.2.0/install/lib/libopencv_imgproc.3.2.0.dylib
filter: /Users/lmn/opencv-3.2.0/install/lib/libopencv_core.3.2.0.dylib
filter: CMakeFiles/filter.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/lmn/opencv_ws/test_vs/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable filter"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/filter.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/filter.dir/build: filter

.PHONY : CMakeFiles/filter.dir/build

CMakeFiles/filter.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/filter.dir/cmake_clean.cmake
.PHONY : CMakeFiles/filter.dir/clean

CMakeFiles/filter.dir/depend:
	cd /Users/lmn/opencv_ws/test_vs/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/lmn/opencv_ws/test_vs /Users/lmn/opencv_ws/test_vs /Users/lmn/opencv_ws/test_vs/build /Users/lmn/opencv_ws/test_vs/build /Users/lmn/opencv_ws/test_vs/build/CMakeFiles/filter.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/filter.dir/depend
