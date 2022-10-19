#include "Hamming.h"

Hamming::Hamming(std::queue<uint8_t>* buffInput
    , std::queue<uint8_t>* buffOutput
    , int bufferSize) : ProcessData(buffInput, buffOutput, bufferSize) {
        popedBuffer = new int[HAMMING_MATRIX_HEIGHT];
}

void Hamming::iteration() {
    int matrixWidth = HAMMING_MATRIX_WIDTH;
    int matrixHeight = HAMMING_MATRIX_HEIGHT;

    for(int i = 0; i < matrixHeight; i++) {
        popedBuffer[i] = buffInput->front();
        buffInput->pop();
    }
    for(int i = 0; i < matrixWidth; i++) {
        int element = 0;
        for(int j = 0; j < matrixHeight; j++)
            element += popedBuffer[j] * generatorMatrix[j][i];
        buffOutput->push(element);
    }
}