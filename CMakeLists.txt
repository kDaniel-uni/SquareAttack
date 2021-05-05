cmake_minimum_required(VERSION 2.8)

project(main CXX)

include(CTest)
enable_testing()

set(CMAKE_CXX_FLAGS "-std=c++17 -Wall")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 --coverage")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

add_executable(main main.cpp)
add_executable(testKeyExpension testKeyExpension.cpp)
add_executable(testAES testAES.cpp)
add_executable(testHelpers testHelpers.cpp)
add_executable(testSquareAttack testSquareAttack.cpp)

add_library(lib keyExpension.cpp helpers.cpp aes.cpp squareAttack.cpp)

target_link_libraries(main lib)
target_link_libraries(testKeyExpension lib)
target_link_libraries(testAES lib)
target_link_libraries(testHelpers lib)
target_link_libraries(testSquareAttack lib)

add_test(test_Shift ./testHelpers Shift)
add_test(test_SBoxCol ./testHelpers SBoxCol)
add_test(test_Rcon ./testHelpers Rcon)
add_test(test_LookupTable ./testHelpers LookupTable)
add_test(test_ParseKey ./testHelpers ParseKey)
add_test(test_ParseKeyRows ./testHelpers ParseKeyRows)
add_test(test_ParseTableau ./testHelpers ParseTableau)
add_test(test_ParseTableauRows ./testHelpers ParseTableauRows)
add_test(test_ArrayXor ./testHelpers ArrayXor)
add_test(test_concat ./testHelpers concat)
add_test(test_mixCol ./testHelpers mixCol)
add_test(test_getNextRoundKey ./testHelpers getNextRoundKey)

add_test(test_NextRoundKey ./testKeyExpension NextRoundKey)
add_test(test_KeyExpension ./testKeyExpension KeyExpension)

add_test(test_AES ./testAES AES)
add_test(test_AESDecipher ./testAES AESDecipher)
add_test(test_AddRoundKey ./testAES AddRoundKey)
add_test(test_ShiftRow ./testAES ShiftRow)
add_test(test_MixColumns ./testAES MixColumns)
add_test(test_SubBytes ./testAES SubBytes)
