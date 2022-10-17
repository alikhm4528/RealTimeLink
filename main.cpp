#define INPUT_FILE "/home/alikhm/100G/project/RealTimeLink/RealTimeLink/Database/inputData.bin"
#define OUTPUT_FILE "/home/alikhm/100G/project/RealTimeLink/RealTimeLink/Database/outputData.bin"

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
#include "ReadFromFile.hpp"
#include "WriteToFile.hpp"
#include "Interleaving.hpp"
#include "Hamming.hpp"

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
    ReadObject = new ReadFromFile(&inputBuffer, INPUT_FILE, INPUT_BUFFER_SIZE);
    WriteObject = new WriteToFile(&outputBuffer, OUTPUT_FILE, OUTPUT_BUFFER_SIZE);

    #ifdef INTERLEAVING
    std::cout << "Interleaving Algorithem\n";
    ProcessObject = new Interleaving(&inputBuffer
        , &outputBuffer
        , ReadObject
        , INPUT_BUFFER_SIZE);
    #else
    std::cout << "Hamming Algorithem\n";
    ProcessObject = new Hamming(&inputBuffer
        , &outputBuffer
        , ReadObject
        , INPUT_BUFFER_SIZE);
    #endif

    ReadThread = new std::thread(&ReadFromFile::read, ReadObject);
    ProcessDataThread = new std::thread(&ProcessData::run, ProcessObject);
    WriteThread = new std::thread(&WriteToFile::write, WriteObject, ProcessObject);

    ReadThread->join();
    ProcessDataThread->join();
    WriteThread->join();

    return 0;
}