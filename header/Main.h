#ifndef PREFIX
#define PREFIX 
    "/home/alikhm/100G/project/RealTimeLink/RealTimeLink/Database/"
#endif

#define getAddress(file) (std::string)PREFIX + file

#if !defined INTERLEAVING && !defined HAMMING
    #define INTERLEAVING
#endif

#ifdef INTERLEAVING
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

class Main {
    private:
        ReadFromFile* ReadObject;
        WriteToFile* WriteObject;
        ProcessData* ProcessObject;
        std::queue<uint8_t>* inputBuffer;
        std::queue<uint8_t>* outputBuffer;

        std::thread* ReadThread;
        std::thread* WriteThread;
        std::thread* ProcessDataThread;
    public:
        void run();
    private:
        void timerCount();
        void initBuffers();
        void initReadObject();
        void initWriteObject();
        void initProcessObject();
        void initThreads();
        void waitUntilAllThreadsJoined();
    
};