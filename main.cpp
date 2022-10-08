#define INPUT_FILE "/home/alikhm/100G/project/RealTimeLink/Code Base/Database/inputData.bin"
#define OUTPUT_FILE "/home/alikhm/100G/project/RealTimeLink/Code Base/Database/outputData.bin"

#if !defined INTERLEAVING && !defined HAMMING
#define INTERLEAVING
#endif

#include <iostream>
#include <thread>
#include <chrono>
#include "ReadFromFile.hpp"
#include "WriteToFile.hpp"
#include "Interleaving.hpp"
#include "Hamming.hpp"

int cnt = 1;

ReadFromFile* ReadObject;
WriteToFile* WriteObject;
std::queue<int> inputBuffer;
std::queue<int> outputBuffer;
std::queue<int> copy;

std::thread* ReadThread;
std::thread* WriteThread;
std::thread* ProcessDataThread;

class InterleavingWaitable : public Interleaving {
    public:
        InterleavingWaitable(std::queue<int>* inputBuffer, std::queue<int>* outputBuffer) 
            : Interleaving(inputBuffer, outputBuffer) {}
        
        void run() {
            if(ReadThread->joinable())
                ReadThread->join();
            Interleaving::run();
        }
} InterleavingObject(&inputBuffer, &outputBuffer);

class HammingWaitable : public Hamming {
    public:
        HammingWaitable(std::queue<int>* inputBuffer, std::queue<int>* outputBuffer) 
            : Hamming(inputBuffer, outputBuffer) {}
        
        void run() {
            if(ReadThread->joinable())
                ReadThread->join();
            Hamming::run();
        } 
} HammingObject(&inputBuffer, &outputBuffer);

int main() {

    ReadObject = new ReadFromFile(&inputBuffer, INPUT_FILE, 1000000);

    #ifdef INTERLEAVING
    std::cout << "Interleaving Algorithem\n";
    WriteObject = new WriteToFile(&outputBuffer, OUTPUT_FILE, 1000000);
    #else
    std::cout << "Hamming Algorithem\n";
    WriteObject = new WriteToFile(&outputBuffer, OUTPUT_FILE, 1750000);
    #endif

    for(int i = 0; i < 10; i++) {
        ReadThread = new std::thread(&ReadFromFile::read, ReadObject);

        #ifdef INTERLEAVING
        ProcessDataThread = new std::thread(&InterleavingWaitable::run, InterleavingObject);

        if(ProcessDataThread->joinable()) 
            ProcessDataThread->join();
        #else
        ProcessDataThread = new std::thread(&HammingWaitable::run, HammingObject);

        if(ProcessDataThread->joinable()) 
            ProcessDataThread->join();
        #endif

        std::this_thread::sleep_for(std::chrono::seconds(1));

        WriteThread = new std::thread(&WriteToFile::write, WriteObject);
        if(WriteThread->joinable()) 
            WriteThread->join();
        
        delete ReadThread;
        delete ProcessDataThread;
        delete WriteThread;
        std::cout << "iteration " << cnt++ << "\n";
    }

    delete ReadObject;
    delete WriteObject;

    return 0;
}