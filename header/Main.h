#ifndef PREFIX
#define PREFIX 
    "/home/alikhm/100G/project/RealTimeLink/RealTimeLink/Database/"
#endif

#define getAddress(file) (std::string)PREFIX + file

#include <iostream>
#include <thread>
#include <chrono>
#include <cstdint>
#include "ReadFromFile.h"
#include "WriteToFile.h"
#include "Interleaving.h"
#include "Hamming.h"

enum Algorithm {INTERLEAVING, HAMMING};

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
        Main(Algorithm);
        void run();
    private:
        void timerCount();
        void initBuffers();
        void initReadObject(size_t);
        void initWriteObject(size_t);
        void initInterleaving(size_t);
        void initHamming(size_t);
        void initThreads();
        void waitUntilAllThreadsJoined();
    
};