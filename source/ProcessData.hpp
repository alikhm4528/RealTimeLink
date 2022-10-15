#ifndef PROCESS_DATA_HPP
#define PROCESS_DATA_HPP

#include <queue>

class ProcessData {
    protected:
        std::queue<int>* pbuffInput;
        std::queue<int>* pbuffOutput;
        int* popedBuffer;
        bool endOfProcess;
    public:
        ProcessData(std::queue<int>* pbuffInput, std::queue<int>* pbuffOutput) 
            : pbuffInput(pbuffInput), pbuffOutput(pbuffOutput) {
                endOfProcess = false;
            }

        void run() {
            while(!pbuffInput->empty())
                iteration();
        }

        bool isEndOfProcess() {
            return endOfProcess;
        }
    protected:
        virtual void iteration() {}
};
#endif