cmake_minimum_required(VERSION 3.9)
project(HttpServer)

set(CMAKE_CXX_STANDARD 11)

INCLUDE_DIRECTORIES(/usr/local/include)
LINK_DIRECTORIES(/usr/local/lib)

AUX_SOURCE_DIRECTORY(./ SRC_CURR)

set(SOURCE_FILES  ${SRC_CURR})

add_executable(HttpServer ${SOURCE_FILES})

TARGET_LINK_LIBRARIES(HttpServer pthread)