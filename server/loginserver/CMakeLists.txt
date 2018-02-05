cmake_minimum_required(VERSION 3.7)
project(loginserver)

set(CMAKE_CXX_STANDARD 11)

#AUX_SOURCE_DIRECTORY(./ SOURCE_FILES)
INCLUDE_DIRECTORIES(./ ../util ../util/protobuf)
LINK_DIRECTORIES(./ ../util ../util/protobuf)

SET(SOURCE_FILES main.cpp YLLoginConn.h YLLoginConn.cpp)

add_executable(loginserver ${SOURCE_FILES})

find_package(Protobuf REQUIRED)

TARGET_LINK_LIBRARIES(loginserver util protobuf)