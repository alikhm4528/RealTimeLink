#ifndef PROCESS_DATA_H
#define PROCESS_DATA_H

#include <queue>
#include <cstdint>
#include "ReadFromFile.h"

class ProcessData {
    protected:
        std::queue<uint8_t>* buffInput;
        std::queue<uint8_t>* buffOutput;
        int* popedBuffer;
        int bufferSize;
    public:
        ProcessData(std::queue<uint8_t>* buffInput
            , std::queue<uint8_t>* buffOutput
            , int bufferSize);

        void run();
        void doIterations();

    protected:
        virtual void iteration() {}
};
#endif