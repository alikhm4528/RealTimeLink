#define INPUT_FILE "/home/alikhm/100G/project/RealTimeLink/Code Base/Database/inputData.bin"
#define OUTPUT_FILE "/home/alikhm/100G/project/RealTimeLink/Code Base/Database/outputData.bin"

#include <iostream>
#include <thread>
#include <chrono>
#include "ReadFromFile.hpp"
#include "WriteToFile.hpp"
#include "Interleaving.hpp"
#include "Hamming.hpp"

ReadFromFile* ReadObject;
WriteToFile* WriteObject;
std::queue<int> inputBuffer;
std::queue<int> outputBuffer;

std::thread* ReadThread;
std::thread* WriteThread;
std::thread* InterleavingThread;

class InterleavingWaitable : public Interleaving {
    public:
        InterleavingWaitable(std::queue<int>* inputBuffer, std::queue<int>* outputBuffer) 
            : Interleaving(inputBuffer, outputBuffer) {}
        void run() {
            std::cout << "BEFORE\n";
            if(ReadThread->joinable())
                ReadThread->join();
            std::cout << "AFTER\n";
            Interleaving::run();
        }
} InterleavingObject(&inputBuffer, &outputBuffer);

int main() {

    ReadObject = new ReadFromFile(&inputBuffer, INPUT_FILE, 1000000);
    WriteObject = new WriteToFile(&outputBuffer, OUTPUT_FILE, 1000000);

    // for(int i = 0; i < 10; i++) {
        ReadThread = new std::thread(&ReadFromFile::read, ReadObject);
        InterleavingThread = new std::thread(&InterleavingWaitable::run, InterleavingObject);
        if(InterleavingThread->joinable()) 
            InterleavingThread->join();

        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << inputBuffer.size() << " " << outputBuffer.size() << "\n";
        // WriteThread = new std::thread(&WriteToFile::write, WriteObject);
        // if(WriteThread->joinable()) 
        //     WriteThread->join();
        
        // delete ReadThread;
        // delete InterleavingThread;
        // delete WriteThread;
    // }

    delete ReadObject;
    delete WriteObject;
    // if(ReadThread->joinable())
        // ReadThread->join();

    // while (!inputBuffer.empty()) {
        // std::cout << inputBuffer.front() << " ";
        // inputBuffer.pop();
    // }
    
    return 0;
}