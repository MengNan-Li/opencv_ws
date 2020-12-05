#设置CMAKE最低版本
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
#设置项目名称
SET(PROJECT_NAME edge_detector)
#建立项目
PROJECT(${PROJECT_NAME})
#寻找OpenCV库
# set(OpenCV_DIR /Users/lmn/opencv-3.2.0/install/share/OpenCV)
FIND_PACKAGE(OpenCV REQUIRED)
INCLUDE_DIRECTORIES(${OpenCV_INCLUDE_DIRS})
#打印调试信息
MESSAGE(STATUS "Project: ${PROJECT_NAME}")
MESSAGE(STATUS "OpenCV library status:")
MESSAGE(STATUS "    version: ${OpenCV_VERSION}")
MESSAGE(STATUS "    libraries: ${OpenCV_LIBS}")
MESSAGE(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")



ADD_EXECUTABLE(edges_detected ./src/edges_detected.cpp)
TARGET_LINK_LIBRARIES(edges_detected ${OpenCV_LIBS})
