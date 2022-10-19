#include "Interleaving.h"

Interleaving::Interleaving(std::queue<uint8_t>* buffInput
    , std::queue<uint8_t>* buffOutput
    , size_t bufferSize) : ProcessData(buffInput, buffOutput, bufferSize) {
    
    popedBuffer = new uint8_t[INTERLEAVING_INPUT_FRAME_SIZE];
}

void Interleaving::iteration() {
    size_t columnLength = INTERLEAVING_INPUT_FRAME_SIZE / INTERLEAVING_ROW_LENGTH;
    size_t rowLength = INTERLEAVING_ROW_LENGTH;

    for(size_t i = 0; i < INTERLEAVING_INPUT_FRAME_SIZE; i++) {
        popedBuffer[i] = buffInput->front();
        buffInput->pop();
    }

    for(size_t i = 0; i < rowLength; i++) {
        for(size_t j = 0; j < columnLength; j++) {
            buffOutput->push(popedBuffer[j * rowLength + i]);
        }
    }
}