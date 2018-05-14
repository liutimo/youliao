cmake_minimum_required(VERSION 3.9)
project(RouteServer)
set(CMAKE_CXX_STANDARD 11)

INCLUDE_DIRECTORIES(../BaseUtil)
LINK_DIRECTORIES(../BaseUtil)
LINK_LIBRARIES(log4cxx)
AUX_SOURCE_DIRECTORY(./ SRC_CURR)

INCLUDE_DIRECTORIES(/usr/local/include)
LINK_DIRECTORIES(/usr/local/lib)

set(SOURCE_FILES ${SRC_CURR})
find_package(Protobuf REQUIRED)

add_executable(RouteServer ${SRC_CURR})

TARGET_LINK_LIBRARIES(RouteServer BaseUtil protobuf)