#include "Interleaving.h"

Interleaving::Interleaving(std::queue<uint8_t>* buffInput
    , std::queue<uint8_t>* buffOutput
    , int bufferSize) : ProcessData(buffInput, buffOutput, bufferSize) {
    
    popedBuffer = new int[INTERLEAVING_INPUT_FRAME_SIZE];
}

void Interleaving::iteration() {
    int columnLength = INTERLEAVING_INPUT_FRAME_SIZE / INTERLEAVING_ROW_LENGTH;
    int rowLength = INTERLEAVING_ROW_LENGTH;

    for(int i = 0; i < INTERLEAVING_INPUT_FRAME_SIZE; i++) {
        popedBuffer[i] = buffInput->front();
        buffInput->pop();
    }

    for(int i = 0; i < rowLength; i++) {
        for(int j = 0; j < columnLength; j++) {
            buffOutput->push(popedBuffer[j * rowLength + i]);
        }
    }
}