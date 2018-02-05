cmake_minimum_required(VERSION 3.7)
project(loginserver)

set(CMAKE_CXX_STANDARD 11)

AUX_SOURCE_DIRECTORY(./ SOURCE_FILES)
INCLUDE_DIRECTORIES(./ ../util)
LINK_DIRECTORIES(./ ../util)

add_executable(loginserver ${SOURCE_FILES})

TARGET_LINK_LIBRARIES(loginserver util)