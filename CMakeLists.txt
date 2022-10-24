cmake_minimum_required(VERSION 3.15.0)
project("RealTimeLink")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

include_directories(${PROJECT_SOURCE_DIR}/header/)

add_compile_definitions(PREFIX="${PROJECT_SOURCE_DIR}/Database/")

add_subdirectory(Process)
add_subdirectory(FileHandle)
add_subdirectory(test)

# Executables
add_executable(${PROJECT_NAME} main.cpp source/Main.cpp)
target_link_libraries(${PROJECT_NAME} Process FileHandle pthread)