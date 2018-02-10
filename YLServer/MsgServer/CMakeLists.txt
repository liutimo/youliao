cmake_minimum_required(VERSION 3.8)
project(MsgServer)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES msg_server.cpp)
add_executable(MsgServer ${SOURCE_FILES})