cmake_minimum_required(VERSION 3.0.0)
project("RealTimeLink")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

include_directories(${PROJECT_SOURCE_DIR}/header/)
include_directories(${PROJECT_SOURCE_DIR}/source/)

# GTest
# add_subdirectory(source)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# debug cpp flags
SET(CMAKE_CXX_FLAGS_DEBUG "-ggdb")

# executables
# add_executable(${PROJECT_NAME}
# source/ReadFromFile.cpp
# main.cpp)

# preprocessors
# add_compile_definitions(BUFFER_SIZE=6)
add_compile_definitions(BUFFER_SIZE=1000000)

add_executable(runUnitTests
# test/SimpleTests.cpp
# test/ReadFromFileTests.cpp
test/ReadFromFileInputDataTest.cpp)
target_link_libraries(runUnitTests gtest gtest_main)
add_test(runUnitTests runUnitTests)
