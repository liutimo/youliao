cmake_minimum_required(VERSION 3.8)
project(test)

set(CMAKE_CXX_STANDARD 11)

INCLUDE_DIRECTORIES(./ ../)
LINK_DIRECTORIES(./ ../)

set(SOURCE_FILES main.cpp)
add_executable(TEST ${SOURCE_FILES})
TARGET_LINK_LIBRARIES(TEST util)
