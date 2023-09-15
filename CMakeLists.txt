cmake_minimum_required(VERSION 3.5)
project(First)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# Add this block to find and include OpenCV
find_package(OpenCV REQUIRED)
MESSAGE("OpenCV version is : ${OpenCV_VERSION}") 
include_directories(${OpenCV_INCLUDE_DIRS})
link_directories(${OpenCV_LIB_DIRS})
add_executable(${PROJECT_NAME} main.cpp)
# Link OpenCV libraries
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
