cmake_minimum_required(VERSION 3.6)
project(c-simplesocket)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES print.h print.c server.c client.c)
add_executable(server print.h print.c server.c)
add_executable(client print.h print.c client.c)