#include <thread>
#include <queue>
#include "Hamming.hpp"
#include "ReadFromFile.hpp"

class HammingProcess : public Hamming {
    private:
        int bufferSize;
    public:
        HammingProcess(std::queue<int>* inputBuffer
            , std::queue<int>* outputBuffer
            , int bufferSize) 
                : Hamming(inputBuffer, outputBuffer), bufferSize(bufferSize) {}
        
        void run(ReadFromFile* ReadObject) {
            while(!ReadObject->isEndOfRead() || !pbuffInput->empty()) {
                if(pbuffInput->size() == bufferSize)
                    Hamming::run();
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
            }
            endOfProcess = true;
        } 
};