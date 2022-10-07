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

# Test Model
if(BUFFER_SIZE STREQUAL 6)
    # add_compile_definitions(BUFFER_SIZE=6)
    # set(TEST_SRC_NAMES
        # test/ReadFromFileTests.cpp)
else()
    # add_compile_definitions(BUFFER_SIZE=1000000)
    # set(TEST_SRC_NAMES
        # test/ReadFromFileInputDataTest.cpp
        # test/ProcessDataTests.cpp)
endif()

set(TEST_SRC_NAMES
# test/SimpleTests.cpp
test/ReadFromFileTests.cpp
test/ProcessDataTests.cpp)

# Tests
add_executable(runUnitTests ${TEST_SRC_NAMES})
target_link_libraries(runUnitTests gtest gtest_main)
add_test(runUnitTests runUnitTests)
