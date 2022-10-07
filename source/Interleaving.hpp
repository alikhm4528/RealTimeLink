#ifndef INTERLEAVING_INPUT_FRAME_SIZE
#define INTERLEAVING_INPUT_FRAME_SIZE 20
#endif

#ifndef INTERLEAVING_ROW_LENGTH
#define INTERLEAVING_ROW_LENGTH 5
#endif

#include "ProcessData.hpp"

class Interleaving : public ProcessData {
    public:
        Interleaving(std::deque<int>* pbuffInput, std::deque<int>* pbuffOutput)
            : ProcessData(pbuffInput, pbuffOutput) {}

        void run(std::deque<int>::iterator startIt) override {
            int columnLength = INTERLEAVING_INPUT_FRAME_SIZE / INTERLEAVING_ROW_LENGTH;
            int rowLength = INTERLEAVING_ROW_LENGTH;

            for(int i = 0; i < rowLength; i++) {
                for(int j = 0; j < columnLength; j++) {
                    pbuffOutput->push_back(*(startIt + j * rowLength + i));
                }
            }
        }
};