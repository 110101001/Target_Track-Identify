PROJECT(tracker)
cmake_minimum_required(VERSION 3.5)

SET(CMAKE_C_COMPILER "/usr/bin/gcc")
SET(CMAKE_CXX_COMPILER "/usr/bin/g++")
#SET(CMAKE_BUILD_TYPE "Debug")
#SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -w -g -ggdb")
#SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories("include/")
ADD_SUBDIRECTORY(src)
add_executable(tracker main.cpp)
link_directories(${OpenCV_LIBRARY_DIRS})
target_link_libraries(tracker src)
target_link_libraries(tracker ${OpenCV_LIBS})

