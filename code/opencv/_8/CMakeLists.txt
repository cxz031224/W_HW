# 添加C++11标准支持
cmake_minimum_required(VERSION 3.16)
project(hsv)
set(CMAKE_CXX_FLAGS "-std=c++11")
 
# 寻找opencv库
find_package(OpenCV REQUIRED)
# 添加头文件
include_directories(${OpenCV_INCLUDE_DIRS})
add_executable(hsv hsv.cpp)
# 链接opencv库
target_link_libraries(hsv ${OpenCV_LIBS})
