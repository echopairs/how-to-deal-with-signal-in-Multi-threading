cmake_minimum_required(VERSION 2.8)

project(siganl)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/include)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

link_libraries(-lprofiler -ltcmalloc pthread)

set(SOURCE_FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/signal_handle.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/include/signal_handle.h)

add_library(signal ${SOURCE_FILES})

add_executable(signal_example examples/signal_example.cpp)

target_link_libraries(signal_example signal)