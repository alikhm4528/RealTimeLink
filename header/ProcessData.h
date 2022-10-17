#ifndef PROCESS_DATA_H
#define PROCESS_DATA_H

#include <queue>
#include <cstdint>
#include "ReadFromFile.h"

class ProcessData {
    protected:
        std::queue<uint8_t>* pbuffInput;
        std::queue<uint8_t>* pbuffOutput;
        int* popedBuffer;
        bool endOfProcess;
        int bufferSize;
        ReadFromFile* ReadObject;
    public:
        ProcessData(std::queue<uint8_t>* pbuffInput
            , std::queue<uint8_t>* pbuffOutput
            , ReadFromFile* ReadObject
            , int bufferSize);

        void run();
        bool isEndOfProcess();

    protected:
        virtual void iteration() {}
};
#endif