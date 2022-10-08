#ifndef PROCESS_DATA_HPP
#define PROCESS_DATA_HPP

#include <queue>

class ProcessData {
    protected:
        std::queue<int>* pbuffInput;
        std::queue<int>* pbuffOutput;
        int* popedBuffer;
    public:
        ProcessData(std::queue<int>* pbuffInput, std::queue<int>* pbuffOutput) 
            : pbuffInput(pbuffInput), pbuffOutput(pbuffOutput) {}
        void run() {
            while(!pbuffInput->empty())
                iteration();
        }
    protected:
        virtual void iteration();
};
#endif