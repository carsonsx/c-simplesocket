cmake_minimum_required(VERSION 3.6)
project(simplechat)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES server.c)
add_executable(simplechat ${SOURCE_FILES})