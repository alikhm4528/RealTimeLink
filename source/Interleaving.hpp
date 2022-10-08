#ifndef INTERLEAVING_INPUT_FRAME_SIZE
#define INTERLEAVING_INPUT_FRAME_SIZE 20
#endif

#ifndef INTERLEAVING_ROW_LENGTH
#define INTERLEAVING_ROW_LENGTH 5
#endif

#include "ProcessData.hpp"

class Interleaving : public ProcessData {
    public:
        Interleaving(std::queue<int>* pbuffInput, std::queue<int>* pbuffOutput)
            : ProcessData(pbuffInput, pbuffOutput) {
                popedBuffer = new int[INTERLEAVING_INPUT_FRAME_SIZE];
            }
    private:
        void iteration() override {
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
};