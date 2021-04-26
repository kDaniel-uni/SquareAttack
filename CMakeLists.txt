cmake_minimum_required(VERSION 2.8)

project(main CXX)

include(CTest)
enable_testing()

set(CMAKE_CXX_FLAGS "-std=c++17 -g3 -Wall --coverage")

add_executable(main main.cpp)
add_executable(testKeyExpension testKeyExpension.cpp)
add_executable(testAES testAES.cpp)
add_executable(testHelpers helpers.cpp)

add_library(lib keyExpension.cpp helpers.cpp aes.cpp)

target_link_libraries(main lib)
target_link_libraries(testKeyExpension lib)
target_link_libraries(testAES lib)
target_link_libraries(testHelpers lib)

add_test(test_Shift ./testHelpers Shift)
add_test(test_SBox ./testHelpers SBox)
add_test(test_Rcon ./testHelpers Rcon)
add_test(test_ParseKey ./testHelpers ParseKey)
add_test(test_ParseTableau ./testHelpers ParseTableau)
add_test(test_ArrayXor ./testHelpers ArrayXor)
add_test(test_concat ./testHelpers concat)

add_test(test_NextRoundKey ./testKeyExpension NextRoundKey)
add_test(test_KeyExpension ./testKeyExpension KeyExpension)

add_test(test_AES ./testAES AES)
