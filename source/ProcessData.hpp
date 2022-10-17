#ifndef PROCESS_DATA_HPP
#define PROCESS_DATA_HPP

#include <queue>
#include "ReadFromFile.hpp"

class ProcessData {
    protected:
        std::queue<int>* pbuffInput;
        std::queue<int>* pbuffOutput;
        int* popedBuffer;
        bool endOfProcess;
        int bufferSize;
        ReadFromFile* ReadObject;
    public:
        ProcessData(std::queue<int>* pbuffInput
            , std::queue<int>* pbuffOutput
            , ReadFromFile* ReadObject
            , int bufferSize) 
                : pbuffInput(pbuffInput)
                , pbuffOutput(pbuffOutput)
                , bufferSize(bufferSize)
                , ReadObject(ReadObject) {
                    endOfProcess = false;
                }

        void run() {
            while(!ReadObject->isEndOfRead() || !pbuffInput->empty()) {
                if(pbuffInput->size() == bufferSize)
                    while(!pbuffInput->empty()) iteration();

                std::this_thread::sleep_for(std::chrono::milliseconds(50));
            }
            endOfProcess = true;
        }

        bool isEndOfProcess() {
            return endOfProcess;
        }
    protected:
        virtual void iteration() {}
};
#endif