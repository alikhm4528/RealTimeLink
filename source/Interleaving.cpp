#include "Interleaving.h"

Interleaving::Interleaving(std::queue<uint8_t>* pbuffInput
    , std::queue<uint8_t>* pbuffOutput
    , ReadFromFile* ReadObject
    , int bufferSize) : ProcessData(pbuffInput, pbuffOutput, ReadObject, bufferSize) {
    
    popedBuffer = new int[INTERLEAVING_INPUT_FRAME_SIZE];
}

void Interleaving::iteration() {
    int columnLength = INTERLEAVING_INPUT_FRAME_SIZE / INTERLEAVING_ROW_LENGTH;
    int rowLength = INTERLEAVING_ROW_LENGTH;

    for(int i = 0; i < INTERLEAVING_INPUT_FRAME_SIZE; i++) {
        popedBuffer[i] = pbuffInput->front();
        pbuffInput->pop();
    }

    for(int i = 0; i < rowLength; i++) {
        for(int j = 0; j < columnLength; j++) {
            pbuffOutput->push(popedBuffer[j * rowLength + i]);
        }
    }
}