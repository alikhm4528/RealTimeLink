#include "Main.h"

Main::Main(Algorithm type) {
    initBuffers();
    initReadObject(1000000);
    
    if(type == INTERLEAVING) {
        initWriteObject(1000000);
        initInterleaving(1000000);
    } else if (type == HAMMING) {
        initWriteObject(1750000);
        initHamming(1000000);
    }
}

void Main::run() {
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

void Main::initReadObject(size_t inputBufferSize) {
    ReadObject = new ReadFromFile(inputBuffer
        , getAddress("inputData.bin")
        , inputBufferSize);
}

void Main::initWriteObject(size_t outputBufferSize) {
    WriteObject = new WriteToFile(outputBuffer
        , getAddress("outputData.bin")
        , outputBufferSize);
}

void Main::initInterleaving(size_t inputBufferSize) {
    ProcessObject = new Interleaving(inputBuffer
        , outputBuffer
        , inputBufferSize);
}

void Main::initHamming(size_t inputBufferSize) {
    ProcessObject = new Hamming(inputBuffer
        , outputBuffer
        , inputBufferSize);
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