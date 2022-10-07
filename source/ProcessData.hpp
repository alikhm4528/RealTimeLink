#ifndef PROCESS_DATA_HPP
#define PROCESS_DATA_HPP

#include <deque>

class ProcessData {
    protected:
        std::deque<int>* pbuffInput;
        std::deque<int>* pbuffOutput;
    public:
        ProcessData(std::deque<int>* pbuffInput, std::deque<int>* pbuffOutput) 
            : pbuffInput(pbuffInput), pbuffOutput(pbuffOutput) {}
        virtual void run(std::deque<int>::iterator) {};
};
#endif