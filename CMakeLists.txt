cmake_minimum_required(VERSION 2.8) 
project (final)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)

find_package(Boost COMPONENTS program_options filesystem system REQUIRED)
find_library(httpParser NAMES http_parser REQUIRED)

set(SRC_LIST src/main.cpp src/server.cpp src/daemonize.c)
include_directories(src)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

add_executable(${PROJECT_NAME} ${SRC_LIST})
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES} ${httpParser})
