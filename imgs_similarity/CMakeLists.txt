#设置CMAKE最低版本
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
#设置项目名称
SET(PROJECT_NAME imgs_similraty)
#建立项目
PROJECT(${PROJECT_NAME})
#寻找OpenCV库
#set(OpenCV_DIR /Users/lmn/opencv-3.2.0/install/share/OpenCV)
FIND_PACKAGE(OpenCV 2 REQUIRED)
INCLUDE_DIRECTORIES(${OpenCV_INCLUDE_DIRS})
#打印调试信息
MESSAGE(STATUS "Project: ${PROJECT_NAME}")
MESSAGE(STATUS "OpenCV library status:")
MESSAGE(STATUS "    version: ${OpenCV_VERSION}")
MESSAGE(STATUS "    libraries: ${OpenCV_LIBS}")
MESSAGE(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")

#获取代码，在项目中，将所有代码都放在src文件夹中
AUX_SOURCE_DIRECTORY(src DIR_SRCS)
MESSAGE(STATUS "Src file: ${DIR_SRCS}")


ADD_EXECUTABLE(base_orb ./src/base_orb.cpp)
TARGET_LINK_LIBRARIES(base_orb ${OpenCV_LIBS})

ADD_EXECUTABLE(base_hist ./src/base_hist.cpp)
TARGET_LINK_LIBRARIES(base_hist ${OpenCV_LIBS})

ADD_EXECUTABLE(base_hash ./src/base_hash.cpp)
TARGET_LINK_LIBRARIES(base_hash ${OpenCV_LIBS})