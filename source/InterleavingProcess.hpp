#include <thread>
#include <queue>
#include "Interleaving.hpp"
#include "ReadFromFile.hpp"

class InterleavingProcess : public Interleaving {
    private:
        int bufferSize;
    public:
        InterleavingProcess(std::queue<int>* inputBuffer
            , std::queue<int>* outputBuffer
            , int bufferSize) 
                : Interleaving(inputBuffer, outputBuffer), bufferSize(bufferSize) {}
        
        void run(ReadFromFile* ReadObject) {
            while(!ReadObject->isEndOfRead() || !pbuffInput->empty()) {
                if(pbuffInput->size() == bufferSize)
                    Interleaving::run();
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
            }
            endOfProcess = true;
        }
};