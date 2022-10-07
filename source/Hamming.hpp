#ifndef HAMMING_MATRIX_WIDTH
#define HAMMING_MATRIX_WIDTH 7
#endif

#ifndef HAMMING_MATRIX_HEIGHT
#define HAMMING_MATRIX_HEIGHT 4
#endif

#include "ProcessData.hpp"

class Hamming : public ProcessData {
    private:
        int generatorMatrix[4][7] 
            = {{1, 0, 0, 0, 1, 0, 1}
             , {0, 1, 0, 0, 1, 1, 0}
             , {0, 0, 1, 0, 1, 1, 1}
             , {0, 0, 0, 1, 0, 1, 1}};
    public:
        Hamming(std::deque<int>* pbuffInput, std::deque<int>* pbuffOutput)
            : ProcessData(pbuffInput, pbuffOutput) {}
        
        void run(std::deque<int>::iterator startIt) override {
            int matrixWidth = HAMMING_MATRIX_WIDTH;
            int matrixHeight = HAMMING_MATRIX_HEIGHT;

            for(int i = 0; i < matrixWidth; i++) {
                int element = 0;
                
                for(int j = 0; j < matrixHeight; j++)
                    element += *(startIt + j) * generatorMatrix[j][i];
                pbuffOutput->push_back(element);
            }
        }
};