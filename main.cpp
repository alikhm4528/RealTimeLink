#ifndef PREFIX
#define PREFIX "/home/alikhm/100G/project/RealTimeLink/RealTimeLink/Database/"
#endif

#define getAddress(file) (std::string)PREFIX + file

#if !defined INTERLEAVING && !defined HAMMING
    #define INTERLEAVING
    #define OUTPUT_BUFFER_SIZE 1000000
#elif defined INTERLEAVING
    #define OUTPUT_BUFFER_SIZE 1000000
#else
    #define OUTPUT_BUFFER_SIZE 1750000
#endif

#define INPUT_BUFFER_SIZE 1000000

#include <iostream>
#include <thread>
#include <chrono>
#include <cstdint>
#include "ReadFromFile.h"
#include "WriteToFile.h"
#include "Interleaving.h"
#include "Hamming.h"

void timerCount();

int main() {
    ReadFromFile* ReadObject;
    WriteToFile* WriteObject;
    ProcessData* ProcessObject;
    std::queue<uint8_t>* inputBuffer = new std::queue<uint8_t>();
    std::queue<uint8_t>* outputBuffer = new std::queue<uint8_t>();

    std::thread* ReadThread;
    std::thread* WriteThread;
    std::thread* ProcessDataThread;

    ReadObject = new ReadFromFile(inputBuffer
        , getAddress("inputData.bin")
        , INPUT_BUFFER_SIZE);
    WriteObject = new WriteToFile(outputBuffer
        , getAddress("outputData.bin")
        , OUTPUT_BUFFER_SIZE);

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

    ReadThread = new std::thread(&ReadFromFile::read, ReadObject);
    ProcessDataThread = new std::thread(&ProcessData::run, ProcessObject);
    WriteThread = new std::thread(&WriteToFile::write, WriteObject);

    timerCount();

    ReadThread->join();
    ProcessDataThread->join();
    WriteThread->join();

    return 0;
}

void timerCount() {
    size_t timer = 1;
    
    while(timer <= 10) {
        auto oneSecond = std::chrono::steady_clock::now() + std::chrono::seconds(1);
        std::cout << "\rtimer = " << timer++;
        std::cout.flush();
        std::this_thread::sleep_until(oneSecond);
    }
    std::cout << "\n";
}
