project("FileHandle")

set(FILE_HANDLE_LIBS
source/FileHandler.cpp
source/ReadChunk.cpp
source/ReadFromFile.cpp
source/WriteChunk.cpp
source/WriteToFile.cpp)

add_library(FileHandle SHARED ${FILE_HANDLE_LIBS})

target_include_directories(FileHandle PUBLIC header)