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
#include "InterleavingProcess.hpp"
#include "HammingProcess.hpp"

int cnt = 1;

class WriteToFile;
class ReadFromFile;

ReadFromFile* ReadObject;
WriteToFile* WriteObject;
ProcessData* ProcessObject;
std::queue<int> inputBuffer;
std::queue<int> outputBuffer;

std::thread* ReadThread;
std::thread* WriteThread;
std::thread* ProcessDataThread;

int main() {
    ReadObject = new ReadFromFile(&inputBuffer, INPUT_FILE, 1000000);
    ReadThread = new std::thread(&ReadFromFile::read, ReadObject);

    #ifdef INTERLEAVING
    std::cout << "Interleaving Algorithem\n";
    WriteObject = new WriteToFile(&outputBuffer, OUTPUT_FILE, 1000000);
    ProcessObject = new InterleavingProcess(&inputBuffer, &outputBuffer, 1000000);
    ProcessDataThread = new std::thread(
        &InterleavingProcess::run
        , (InterleavingProcess*)ProcessObject
        , ReadObject);
    #else
    std::cout << "Hamming Algorithem\n";
    WriteObject = new WriteToFile(&outputBuffer, OUTPUT_FILE, 1750000);
    ProcessObject = new HammingProcess(&inputBuffer, &outputBuffer, 1000000);
    ProcessDataThread = new std::thread(
        &HammingProcess::run
        , (HammingProcess*)ProcessObject
        , ReadObject);
    #endif

    WriteThread = new std::thread(&WriteToFile::write, WriteObject, ProcessObject);

    WriteThread->join();
    ReadThread->join();
    ProcessDataThread->join();

    return 0;
}