PROJECT(tracker)
cmake_minimum_required(VERSION 3.5)

SET(CMAKE_BUILD_TYPE "Debug")
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -w -g -ggdb")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${DIR_TOOT_SRCS}/bin)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories("include/")
add_executable(tracker main.c)
link_directories(${OpenCV_LIBRARY_DIRS})
target_link_libraries(tracker ${OpenCV_LIBS})

