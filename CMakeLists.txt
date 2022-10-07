cmake_minimum_required(VERSION 3.0.0)
project("RealTimeLink")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

include_directories(${PROJECT_SOURCE_DIR}/header/)
include_directories(${PROJECT_SOURCE_DIR}/source/)

# GTest
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# Debug cpp flags
SET(CMAKE_CXX_FLAGS_DEBUG "-ggdb")

# Executables
# add_executable(${PROJECT_NAME}
# source/ReadFromFile.cpp
# main.cpp)

# Tests
set(TEST_SOURCES
# test/SimpleTests.cpp
test/ReadFromFileTests.cpp
test/ProcessDataTests.cpp
test/WriteToFileTests.cpp)
add_executable(runUnitTests ${TEST_SOURCES})
target_link_libraries(runUnitTests gtest gtest_main)
add_test(runUnitTests runUnitTests)
