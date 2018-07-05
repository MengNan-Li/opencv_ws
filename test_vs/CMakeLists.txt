#设置CMAKE最低版本
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
#设置项目名称
SET(PROJECT_NAME Image_Test_01)
#建立项目
PROJECT(${PROJECT_NAME})
#寻找OpenCV库
set(OpenCV_DIR /Users/lmn/opencv-3.2.0/install/share/OpenCV)
FIND_PACKAGE(OpenCV REQUIRED)
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
#编译可执行程序
ADD_EXECUTABLE(${PROJECT_NAME} ./src/main.cpp)
#添加链接库
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${OpenCV_LIBS})

# 第一个例子，腐蚀，还有多张图片在一个窗口中显示
ADD_EXECUTABLE(erode ./src/erode.cpp)
TARGET_LINK_LIBRARIES(erode ${OpenCV_LIBS})
# 绘画功能：椭圆、方框、圆等
ADD_EXECUTABLE(draw ./src/draw.cpp)
TARGET_LINK_LIBRARIES(draw ${OpenCV_LIBS})
# 循环进行像素操作
ADD_EXECUTABLE(pixel_operater ./src/pixel_operater.cpp)
TARGET_LINK_LIBRARIES(pixel_operater ${OpenCV_LIBS})
# 感兴趣区ROI设置 
ADD_EXECUTABLE(ROI ./src/ROI.cpp)
TARGET_LINK_LIBRARIES(ROI ${OpenCV_LIBS})
# 文件读写：XML、Yaml
ADD_EXECUTABLE(fileStorage ./src/fileStorage.cpp)
TARGET_LINK_LIBRARIES(fileStorage ${OpenCV_LIBS})
# 线性滤波、非线性滤波
ADD_EXECUTABLE(filter ./src/filter.cpp)
TARGET_LINK_LIBRARIES(filter ${OpenCV_LIBS})
# 形态学滤波：腐蚀、膨胀, 有滑动条
ADD_EXECUTABLE(morphology ./src/morphology.cpp)
TARGET_LINK_LIBRARIES(morphology ${OpenCV_LIBS})
# 图片尺寸缩放：resize、pryUp、pryDown
ADD_EXECUTABLE(size_operation ./src/size_operation.cpp)
TARGET_LINK_LIBRARIES(size_operation ${OpenCV_LIBS})
# 阈值
ADD_EXECUTABLE(threshold ./src/threshold.cpp)
TARGET_LINK_LIBRARIES(threshold ${OpenCV_LIBS})
# 边缘检测
ADD_EXECUTABLE(edges_detected ./src/edges_detected.cpp)
TARGET_LINK_LIBRARIES(edges_detected ${OpenCV_LIBS})
# 霍夫变换
ADD_EXECUTABLE(hough ./src/hough.cpp)
TARGET_LINK_LIBRARIES(hough ${OpenCV_LIBS})