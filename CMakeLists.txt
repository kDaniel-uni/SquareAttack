cmake_minimum_required(VERSION 2.8)

project(main C)

include(CTest)
enable_testing()

set(CMAKE_C_FLAGS "-std=c99 -g3 -Wall --coverage")

add_executable(main main.c)
add_executable(testKeyExpension testKeyExpension.c)

add_library(lib keyExpension.c aes.c)

target_link_libraries(main lib)
target_link_libraries(testKeyExpension lib)

add_test(testKeyExpension ./testKeyExpension)
