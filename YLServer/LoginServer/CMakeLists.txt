cmake_minimum_required(VERSION 3.7)
project(LoginServer)
set(CMAKE_CXX_STANDARD 11)

INCLUDE_DIRECTORIES(../BaseUtil)
INCLUDE_DIRECTORIES(/usr/local/include)
LINK_DIRECTORIES(/usr/local/lib)

LINK_DIRECTORIES(../BaseUtil)
LINK_LIBRARIES(log4cxx)

AUX_SOURCE_DIRECTORY(./ SRC_CURR)

set(SOURCE_FILES ${SRC_CURR})

find_package(Protobuf REQUIRED)
add_executable(LoginServer ${SOURCE_FILES})

TARGET_LINK_LIBRARIES(LoginServer BaseUtil protobuf)
