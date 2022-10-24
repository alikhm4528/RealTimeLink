#include "Main.h"

void Main::run() {
    initBuffers();
    initReadObject();
    initWriteObject();
    initProcessObject();

    initThreads();

    timerCount();

    waitUntilAllThreadsJoined();
}

void Main::timerCount() {
    size_t timer = 1;
    
    while(timer <= 10) {
        auto oneSecond = std::chrono::steady_clock::now()
            + std::chrono::seconds(1);
        std::cout << "\rtimer = " << timer++;
        std::cout.flush();
        std::this_thread::sleep_until(oneSecond);
    }
    std::cout << "\n";
}

void Main::initBuffers() {
    inputBuffer = new std::queue<uint8_t>();
    outputBuffer = new std::queue<uint8_t>();
}

void Main::initReadObject() {
    ReadObject = new ReadFromFile(inputBuffer
        , getAddress("inputData.bin")
        , INPUT_BUFFER_SIZE);
}

void Main::initWriteObject() {
    WriteObject = new WriteToFile(outputBuffer
        , getAddress("outputData.bin")
        , OUTPUT_BUFFER_SIZE);
}

void Main::initProcessObject() {
    #ifdef INTERLEAVING
    std::cout << "Interleaving Algorithem\n";
    ProcessObject = new Interleaving(inputBuffer
        , outputBuffer
        , INPUT_BUFFER_SIZE);
    #else
    std::cout << "Hamming Algorithem\n";
    ProcessObject = new Hamming(inputBuffer
        , outputBuffer
        , INPUT_BUFFER_SIZE);
    #endif
}

void Main::initThreads() {
    ReadThread = new std::thread(&ReadFromFile::read, ReadObject);
    ProcessDataThread = new std::thread(&ProcessData::run
        , ProcessObject);
    WriteThread = new std::thread(&WriteToFile::write, WriteObject);
}

void Main::waitUntilAllThreadsJoined() {
    if(ReadThread->joinable()) ReadThread->join();
    if(ProcessDataThread->joinable()) ProcessDataThread->join();
    if(WriteThread->joinable()) WriteThread->join();
}