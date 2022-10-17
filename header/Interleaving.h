#ifndef INTERLEAVING_INPUT_FRAME_SIZE
#define INTERLEAVING_INPUT_FRAME_SIZE 20
#endif

#ifndef INTERLEAVING_ROW_LENGTH
#define INTERLEAVING_ROW_LENGTH 5
#endif

#include <cstdint>
#include "ProcessData.h"

class Interleaving : public ProcessData {
    public:
        Interleaving(std::queue<uint8_t>* pbuffInput
            , std::queue<uint8_t>* pbuffOutput
            , ReadFromFile* ReadObject
            , int bufferSize);
    private:
        void iteration() override;
};