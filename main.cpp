#define INPUT_FILE "/home/alikhm/100G/project/RealTimeLink/RealTimeLink/Database/inputData.bin"
#define OUTPUT_FILE "/home/alikhm/100G/project/RealTimeLink/RealTimeLink/Database/outputData.bin"

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

class WriteWaitable;

ReadFromFile* ReadObject;
WriteWaitable* WriteObject;
std::queue<int> inputBuffer;
std::queue<int> outputBuffer;

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

class WriteWaitable : public WriteToFile {
    public:
        WriteWaitable(std::queue<int>* pbuff, std::string fileName, int outputBufferSize)
            : WriteToFile(pbuff, fileName, outputBufferSize) {}

        void write() {
            if(ProcessDataThread->joinable())
                ProcessDataThread->join();
            WriteToFile::write();
        }
};

int main() {
    ReadObject = new ReadFromFile(&inputBuffer, INPUT_FILE, 1000000);

    #ifdef INTERLEAVING
    std::cout << "Interleaving Algorithem\n";
    WriteObject = new WriteWaitable(&outputBuffer, OUTPUT_FILE, 1000000);
    #else
    std::cout << "Hamming Algorithem\n";
    WriteObject = new WriteWaitable(&outputBuffer, OUTPUT_FILE, 1750000);
    #endif

    for(int i = 0; i < 10; i++) {
        ReadThread = new std::thread(&ReadFromFile::read, ReadObject);

        #ifdef INTERLEAVING
        ProcessDataThread = new std::thread(&InterleavingWaitable::run, InterleavingObject);
        #else
        ProcessDataThread = new std::thread(&HammingWaitable::run, HammingObject);
        #endif

        WriteThread = new std::thread(&WriteWaitable::write, WriteObject);

        std::this_thread::sleep_for(std::chrono::seconds(1));
        
        std::cout << "iteration " << cnt++ << "\n";
    }
    return 0;
}