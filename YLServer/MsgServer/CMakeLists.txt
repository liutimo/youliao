cmake_minimum_required(VERSION 3.8)
project(MsgServer)

set(CMAKE_CXX_STANDARD 11)

INCLUDE_DIRECTORIES(../BaseUtil)
LINK_DIRECTORIES(../BaseUtil)

AUX_SOURCE_DIRECTORY(./ SRC_LIST)


set(SOURCE_FILES ${SRC_LIST})

find_package(Protobuf REQUIRED)

add_executable(MsgServer ${SOURCE_FILES} DBServConn.h DBServConn.cpp)


TARGET_LINK_LIBRARIES(MsgServer BaseUtil log4cxx protobuf)