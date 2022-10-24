project("Process")

set(PROCESS_LIBS
source/ProcessData.cpp
source/Hamming.cpp
source/Interleaving.cpp)

add_library(Process SHARED ${PROCESS_LIBS})

target_include_directories(Process PUBLIC header)