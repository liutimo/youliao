cmake_minimum_required(VERSION 3.8)
project(DBServer)

set(CMAKE_CXX_STANDARD 11)

AUX_SOURCE_DIRECTORY(./ SRC_LIST)

set(SOURCE_FILES ${SRC_LIST})

INCLUDE_DIRECTORIES(../BaseUtil)
LINK_DIRECTORIES(../BaseUtil)

find_package(Protobuf REQUIRED)
add_executable(DBServer ${SOURCE_FILES})

TARGET_LINK_LIBRARIES(DBServer BaseUtil mysqlclient pthread log4cxx protobuf)