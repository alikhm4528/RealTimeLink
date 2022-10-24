cmake_minimum_required(VERSION 3.15.0)
project("RealTimeLink")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

include_directories(${PROJECT_SOURCE_DIR}/header/)

# GTest
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# Debug cpp flags
SET(CMAKE_CXX_FLAGS_DEBUG "-ggdb")

if(${ALG} STREQUAL "INTERLEAVING")
	add_compile_definitions(INTERLEAVING)
else()
	add_compile_definitions(HAMMING)
endif()

add_compile_definitions(PREFIX="${PROJECT_SOURCE_DIR}/Database/")

add_subdirectory(Process)
add_subdirectory(FileHandle)

# Executables
add_executable(${PROJECT_NAME} main.cpp source/Main.cpp)
target_link_libraries(${PROJECT_NAME} Process FileHandle pthread)

# Tests
set(TEST_SOURCES
test/ReadFromFileTests.cpp
test/ProcessDataTests.cpp
test/WriteToFileTests.cpp)

add_executable(runUnitTests ${TEST_SOURCES})
target_link_libraries(runUnitTests gtest gtest_main Process FileHandle pthread)
add_test(runUnitTests runUnitTests)
