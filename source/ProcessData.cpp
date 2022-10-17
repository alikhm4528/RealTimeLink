#include "ProcessData.h"

ProcessData::ProcessData(std::queue<uint8_t>* pbuffInput
    , std::queue<uint8_t>* pbuffOutput
    , ReadFromFile* ReadObject
    , int bufferSize)
        : pbuffInput(pbuffInput)
        , pbuffOutput(pbuffOutput)
        , bufferSize(bufferSize)
        , ReadObject(ReadObject) {

    endOfProcess = false;
}

void ProcessData::run() {
    while(!ReadObject->isEndOfRead() || !pbuffInput->empty()) {
        if(pbuffInput->size() == bufferSize)
            while(!pbuffInput->empty()) iteration();

        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
    endOfProcess = true;
}

bool ProcessData::isEndOfProcess() {
    return endOfProcess;
}