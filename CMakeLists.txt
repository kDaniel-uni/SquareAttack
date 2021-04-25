cmake_minimum_required(VERSION 2.8)

project(main CXX)

include(CTest)
enable_testing()

set(CMAKE_CXX_FLAGS "-std=c++17 -g3 -Wall --coverage")

add_executable(main main.cpp)
add_executable(testKeyExpension testKeyExpension.cpp)

#add_library(lib keyExpension.cpp aes.cpp)
add_library(lib keyExpension.cpp helpers.cpp)

target_link_libraries(main lib)
target_link_libraries(testKeyExpension lib)

add_test(test_Shift ./testKeyExpension Shift)
add_test(test_SBox ./testKeyExpension SBox)
add_test(test_Rcon ./testKeyExpension Rcon)
add_test(test_ParseKey ./testKeyExpension ParseKey)
add_test(test_ParseTableau ./testKeyExpension ParseTableau)
add_test(test_NextRoundKey ./testKeyExpension NextRoundKey)
add_test(test_ArrayXor ./testKeyExpension ArrayXor)
add_test(test_KeyExpension ./testKeyExpension KeyExpension)
add_test(test_concat ./testKeyExpension concat)
