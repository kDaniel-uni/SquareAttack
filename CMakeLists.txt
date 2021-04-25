cmake_minimum_required(VERSION 2.8)

project(main CXX)

include(CTest)
enable_testing()

set(CMAKE_CXX_FLAGS "-std=c++17 -g3 -Wall --coverage")

add_executable(main main.cpp)
add_executable(testKeyExpension testKeyExpension.cpp)

#add_library(lib keyExpension.cpp aes.cpp)
add_library(lib keyExpension.cpp tools.cpp)

target_link_libraries(main lib)
target_link_libraries(testKeyExpension lib)

add_test(testKeyExpension ./testKeyExpension)
