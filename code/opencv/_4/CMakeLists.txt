# 添加C++11标准支持
cmake_minimum_required(VERSION 3.16)
project(channelSeparation)
set(CMAKE_CXX_FLAGS "-std=c++11")
 
# 寻找opencv库
find_package(OpenCV REQUIRED)
# 添加头文件
include_directories(${OpenCV_INCLUDE_DIRS})
add_executable(channelSeparation channelSeparation.cpp)
# 链接opencv库
target_link_libraries(channelSeparation ${OpenCV_LIBS})
