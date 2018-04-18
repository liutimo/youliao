cmake_minimum_required(VERSION 3.8)
project(DBServer)

set(CMAKE_CXX_STANDARD 11)

AUX_SOURCE_DIRECTORY(./ SRC_LIST)
AUX_SOURCE_DIRECTORY(./business SRC_LIST2)

set(SOURCE_FILES ${SRC_LIST} ${SRC_LIST2} business/SessionModel.cpp business/SessionModel.h)

INCLUDE_DIRECTORIES(/usr/local/include)
LINK_DIRECTORIES(/usr/local/lib)

INCLUDE_DIRECTORIES(../BaseUtil)
LINK_DIRECTORIES(../BaseUtil ./)

find_package(Protobuf REQUIRED)
add_executable(DBServer ${SOURCE_FILES})

TARGET_LINK_LIBRARIES(DBServer BaseUtil mysqlclient pthread log4cxx protobuf hiredis)