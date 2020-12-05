# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.9

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/lmn/opencv_ws/motionDetection

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lmn/opencv_ws/motionDetection/build

# Include any dependencies generated for this target.
include CMakeFiles/FramesDifference1.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/FramesDifference1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/FramesDifference1.dir/flags.make

CMakeFiles/FramesDifference1.dir/FramesDifference/main1.cpp.o: CMakeFiles/FramesDifference1.dir/flags.make
CMakeFiles/FramesDifference1.dir/FramesDifference/main1.cpp.o: ../FramesDifference/main1.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lmn/opencv_ws/motionDetection/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/FramesDifference1.dir/FramesDifference/main1.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/FramesDifference1.dir/FramesDifference/main1.cpp.o -c /home/lmn/opencv_ws/motionDetection/FramesDifference/main1.cpp

CMakeFiles/FramesDifference1.dir/FramesDifference/main1.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/FramesDifference1.dir/FramesDifference/main1.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lmn/opencv_ws/motionDetection/FramesDifference/main1.cpp > CMakeFiles/FramesDifference1.dir/FramesDifference/main1.cpp.i

CMakeFiles/FramesDifference1.dir/FramesDifference/main1.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/FramesDifference1.dir/FramesDifference/main1.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lmn/opencv_ws/motionDetection/FramesDifference/main1.cpp -o CMakeFiles/FramesDifference1.dir/FramesDifference/main1.cpp.s

CMakeFiles/FramesDifference1.dir/FramesDifference/main1.cpp.o.requires:

.PHONY : CMakeFiles/FramesDifference1.dir/FramesDifference/main1.cpp.o.requires

CMakeFiles/FramesDifference1.dir/FramesDifference/main1.cpp.o.provides: CMakeFiles/FramesDifference1.dir/FramesDifference/main1.cpp.o.requires
	$(MAKE) -f CMakeFiles/FramesDifference1.dir/build.make CMakeFiles/FramesDifference1.dir/FramesDifference/main1.cpp.o.provides.build
.PHONY : CMakeFiles/FramesDifference1.dir/FramesDifference/main1.cpp.o.provides

CMakeFiles/FramesDifference1.dir/FramesDifference/main1.cpp.o.provides.build: CMakeFiles/FramesDifference1.dir/FramesDifference/main1.cpp.o


# Object files for target FramesDifference1
FramesDifference1_OBJECTS = \
"CMakeFiles/FramesDifference1.dir/FramesDifference/main1.cpp.o"

# External object files for target FramesDifference1
FramesDifference1_EXTERNAL_OBJECTS =

FramesDifference1: CMakeFiles/FramesDifference1.dir/FramesDifference/main1.cpp.o
FramesDifference1: CMakeFiles/FramesDifference1.dir/build.make
FramesDifference1: /usr/local/lib/libopencv_gapi.so.4.1.1
FramesDifference1: /usr/local/lib/libopencv_stitching.so.4.1.1
FramesDifference1: /usr/local/lib/libopencv_aruco.so.4.1.1
FramesDifference1: /usr/local/lib/libopencv_bgsegm.so.4.1.1
FramesDifference1: /usr/local/lib/libopencv_bioinspired.so.4.1.1
FramesDifference1: /usr/local/lib/libopencv_ccalib.so.4.1.1
FramesDifference1: /usr/local/lib/libopencv_dnn_objdetect.so.4.1.1
FramesDifference1: /usr/local/lib/libopencv_dpm.so.4.1.1
FramesDifference1: /usr/local/lib/libopencv_face.so.4.1.1
FramesDifference1: /usr/local/lib/libopencv_freetype.so.4.1.1
FramesDifference1: /usr/local/lib/libopencv_fuzzy.so.4.1.1
FramesDifference1: /usr/local/lib/libopencv_hdf.so.4.1.1
FramesDifference1: /usr/local/lib/libopencv_hfs.so.4.1.1
FramesDifference1: /usr/local/lib/libopencv_img_hash.so.4.1.1
FramesDifference1: /usr/local/lib/libopencv_line_descriptor.so.4.1.1
FramesDifference1: /usr/local/lib/libopencv_quality.so.4.1.1
FramesDifference1: /usr/local/lib/libopencv_reg.so.4.1.1
FramesDifference1: /usr/local/lib/libopencv_rgbd.so.4.1.1
FramesDifference1: /usr/local/lib/libopencv_saliency.so.4.1.1
FramesDifference1: /usr/local/lib/libopencv_sfm.so.4.1.1
FramesDifference1: /usr/local/lib/libopencv_stereo.so.4.1.1
FramesDifference1: /usr/local/lib/libopencv_structured_light.so.4.1.1
FramesDifference1: /usr/local/lib/libopencv_superres.so.4.1.1
FramesDifference1: /usr/local/lib/libopencv_surface_matching.so.4.1.1
FramesDifference1: /usr/local/lib/libopencv_tracking.so.4.1.1
FramesDifference1: /usr/local/lib/libopencv_videostab.so.4.1.1
FramesDifference1: /usr/local/lib/libopencv_viz.so.4.1.1
FramesDifference1: /usr/local/lib/libopencv_xfeatures2d.so.4.1.1
FramesDifference1: /usr/local/lib/libopencv_xobjdetect.so.4.1.1
FramesDifference1: /usr/local/lib/libopencv_xphoto.so.4.1.1
FramesDifference1: /usr/local/lib/libopencv_shape.so.4.1.1
FramesDifference1: /usr/local/lib/libopencv_datasets.so.4.1.1
FramesDifference1: /usr/local/lib/libopencv_plot.so.4.1.1
FramesDifference1: /usr/local/lib/libopencv_text.so.4.1.1
FramesDifference1: /usr/local/lib/libopencv_dnn.so.4.1.1
FramesDifference1: /usr/local/lib/libopencv_highgui.so.4.1.1
FramesDifference1: /usr/local/lib/libopencv_ml.so.4.1.1
FramesDifference1: /usr/local/lib/libopencv_phase_unwrapping.so.4.1.1
FramesDifference1: /usr/local/lib/libopencv_optflow.so.4.1.1
FramesDifference1: /usr/local/lib/libopencv_ximgproc.so.4.1.1
FramesDifference1: /usr/local/lib/libopencv_video.so.4.1.1
FramesDifference1: /usr/local/lib/libopencv_videoio.so.4.1.1
FramesDifference1: /usr/local/lib/libopencv_imgcodecs.so.4.1.1
FramesDifference1: /usr/local/lib/libopencv_objdetect.so.4.1.1
FramesDifference1: /usr/local/lib/libopencv_calib3d.so.4.1.1
FramesDifference1: /usr/local/lib/libopencv_features2d.so.4.1.1
FramesDifference1: /usr/local/lib/libopencv_flann.so.4.1.1
FramesDifference1: /usr/local/lib/libopencv_photo.so.4.1.1
FramesDifference1: /usr/local/lib/libopencv_imgproc.so.4.1.1
FramesDifference1: /usr/local/lib/libopencv_core.so.4.1.1
FramesDifference1: CMakeFiles/FramesDifference1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/lmn/opencv_ws/motionDetection/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable FramesDifference1"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/FramesDifference1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/FramesDifference1.dir/build: FramesDifference1

.PHONY : CMakeFiles/FramesDifference1.dir/build

CMakeFiles/FramesDifference1.dir/requires: CMakeFiles/FramesDifference1.dir/FramesDifference/main1.cpp.o.requires

.PHONY : CMakeFiles/FramesDifference1.dir/requires

CMakeFiles/FramesDifference1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/FramesDifference1.dir/cmake_clean.cmake
.PHONY : CMakeFiles/FramesDifference1.dir/clean

CMakeFiles/FramesDifference1.dir/depend:
	cd /home/lmn/opencv_ws/motionDetection/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lmn/opencv_ws/motionDetection /home/lmn/opencv_ws/motionDetection /home/lmn/opencv_ws/motionDetection/build /home/lmn/opencv_ws/motionDetection/build /home/lmn/opencv_ws/motionDetection/build/CMakeFiles/FramesDifference1.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/FramesDifference1.dir/depend
