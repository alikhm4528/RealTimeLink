#include "Hamming.h"

Hamming::Hamming(std::queue<uint8_t>* buffInput
    , std::queue<uint8_t>* buffOutput
    , size_t bufferSize) : ProcessData(buffInput, buffOutput, bufferSize) {
        popedBuffer = new uint8_t[HAMMING_MATRIX_HEIGHT];
}

void Hamming::iteration() {
    size_t matrixWidth = HAMMING_MATRIX_WIDTH;
    size_t matrixHeight = HAMMING_MATRIX_HEIGHT;

    for(size_t i = 0; i < matrixHeight; i++) {
        popedBuffer[i] = buffInput->front();
        buffInput->pop();
    }
    for(size_t i = 0; i < matrixWidth; i++) {
        uint8_t element = 0;
        for(size_t j = 0; j < matrixHeight; j++)
            element += popedBuffer[j] * generatorMatrix[j][i];
        buffOutput->push(element);
    }
}