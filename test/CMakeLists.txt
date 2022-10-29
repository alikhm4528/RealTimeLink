cmake_minimum_required(VERSION 3.15.0)
project("Test")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-g -Wall -Wextra")

# GTest
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# Tests
set(TEST_SOURCES
source/ReadFromFileTests.cpp
source/ProcessDataTests.cpp
source/WriteToFileTests.cpp
source/MainTests.cpp
../source/Main.cpp
main.cpp)

add_executable(${PROJECT_NAME} ${TEST_SOURCES})
target_link_libraries(${PROJECT_NAME} gtest Process FileHandle pthread)
add_test(${PROJECT_NAME} COMMAND ${PROJECT_NAME})

# target_include_directories(${PROJCET_NAME} PUBLIC include)