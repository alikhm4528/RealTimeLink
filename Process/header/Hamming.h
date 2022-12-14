#ifndef HAMMING_MATRIX_WIDTH
#define HAMMING_MATRIX_WIDTH 7
#endif

#ifndef HAMMING_MATRIX_HEIGHT
#define HAMMING_MATRIX_HEIGHT 4
#endif

#include "ProcessData.h"

class Hamming : public ProcessData {
    private:
        uint8_t generatorMatrix[4][7] 
            = {{1, 0, 0, 0, 1, 0, 1}
             , {0, 1, 0, 0, 1, 1, 0}
             , {0, 0, 1, 0, 1, 1, 1}
             , {0, 0, 0, 1, 0, 1, 1}};
    public:
        Hamming(std::queue<uint8_t>* buffInput
            , std::queue<uint8_t>* buffOutput
            , size_t bufferSize);
    private:
        void iteration() override;
};