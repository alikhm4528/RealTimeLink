#ifndef PROCESSDATA_HPP
#define PROCESSDATA_HPP

#include <vector>

class ProcessData {
    protected:
        std::vector<int>* pbuffInput;
        std::vector<int>* pbuffOutput;
    public:
        ProcessData(std::vector<int>* pbuffInput, std::vector<int>* pbuffOutput) 
            : pbuffInput(pbuffInput), pbuffOutput(pbuffOutput) {}
        virtual void run(std::vector<int>::iterator) {};
};
#endif