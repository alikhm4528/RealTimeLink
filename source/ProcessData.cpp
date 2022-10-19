#include "ProcessData.h"
#include <iostream>

ProcessData::ProcessData(std::queue<uint8_t>* buffInput
    , std::queue<uint8_t>* buffOutput
    , size_t bufferSize)
        : buffInput(buffInput)
        , buffOutput(buffOutput)
        , bufferSize(bufferSize) {}

void ProcessData::run() {
    uint8_t cnt = 0;
    while(cnt < 25) {
        cnt++;
        while(buffInput->size() == bufferSize) {
            doIterations();
            cnt = 0;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

void ProcessData::doIterations() {
    while(!buffInput->empty()) iteration();
}
