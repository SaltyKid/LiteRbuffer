cmake_minimum_required(VERSION 3.0)
project(RBUF)

# set(CMAKE_EXPORT_COMPILE_COMMANDS OFF)

# set(CMAKE_BUILD_TYPE Release)
set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_C_FLAGS_DEBUG "-g -Wall")
set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall")
set(CMAKE_C_FLAGS_RELEASE "-Os -DNDEBUG -Wall")
set(CMAKE_CXX_FLAGS_RELEASE "-Os -DNDEBUG -Wall")
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 14)


if(WIN32)
# set(CMAKE_C_COMPILER "D:/mingw/bin/gcc.exe")
# set(CMAKE_CXX_COMPILER "D:/mingw/bin/g++.exe")
else()
set(CMAKE_C_COMPILER "/usr/bin/gcc")
set(CMAKE_CXX_COMPILER "/usr/bin/g++")
endif()

set(
    DIR_SRCS
    examples/main.c
    LiteRbuffer/lite_ring_buffer.c
)

# include path
include_directories(examples LiteRbuffer)

# Target
add_executable(rbuf ${DIR_SRCS})

