#ifndef PROCESS_DATA_H
#define PROCESS_DATA_H

#include <queue>
#include <cstdint>
#include "ReadFromFile.h"

class ProcessData {
    protected:
        std::queue<uint8_t>* buffInput;
        std::queue<uint8_t>* buffOutput;
        uint8_t* popedBuffer;
        size_t bufferSize;
    public:
        ProcessData(std::queue<uint8_t>* buffInput
            , std::queue<uint8_t>* buffOutput
            , size_t bufferSize);

        void run();
        void doIterations();

    protected:
        virtual void iteration() {}
};
#endif