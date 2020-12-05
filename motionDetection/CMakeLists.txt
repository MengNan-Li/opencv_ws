# cmake needs this line
cmake_minimum_required(VERSION 3.1)

# Enable C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# Define project name
project(motionDetection)

# Find OpenCV, you may need to set OpenCV_DIR variable
# to the absolute path to the directory containing OpenCVConfig.cmake file
# via the command line or GUI
find_package(OpenCV REQUIRED)
include_directories(include)
# If the package has been found, several variables will
# be set, you can find the full list with descriptions
# in the OpenCVConfig.cmake file.
# Print some message showing some of them
message(STATUS "OpenCV library status:")
message(STATUS "    config: ${OpenCV_DIR}")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")

# Declare the executable target built from your sources
add_executable(FramesDifference1 FramesDifference/main1.cpp)
# Link your application with OpenCV libraries
target_link_libraries(FramesDifference1 LINK_PRIVATE ${OpenCV_LIBS})

add_executable(FramesDifference2 FramesDifference/main2.cpp)
target_link_libraries(FramesDifference2 LINK_PRIVATE ${OpenCV_LIBS})


# BGDifference，高斯背景差分法动态链接库生成
SET(LIB_BGDIFF_SOURCE
	./BGDifference/BGDifference.h
	./BGDifference/BGDifference.cpp)
ADD_LIBRARY(BGDiff SHARED ${LIB_BGDIFF_SOURCE})
TARGET_LINK_LIBRARIES(BGDiff
	${OpenCV_LIBS})
# 生成BGDifference测试程序
SET(LIB_BGDIFF BGDiff)
ADD_EXECUTABLE(BGDiff_test ./BGDifference/main.cpp)
TARGET_LINK_LIBRARIES(BGDiff_test
	${LIB_BGDIFF})