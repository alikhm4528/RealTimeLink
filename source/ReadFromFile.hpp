#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1000000
#endif

#include <vector>
#include <iostream>
#include <fstream>

class NotEnoughData : public std::exception {};

class ReadFromFile {
    private:
        std::vector<int>* pbuff;
        const std::string fileName;
    public:
        ReadFromFile(std::vector<int>* pbuff, const std::string fileName) 
            : pbuff(pbuff), fileName(fileName) {}

        void readDataFromFile(void) {
            std::ifstream file(fileName, std::ios::in|std::ios::binary);
            char charBuff[BUFFER_SIZE];

            file.read(charBuff, BUFFER_SIZE);
            if(!file) {
                std::cout << file.gcount() << std::endl;
                throw new NotEnoughData;
            }
            for(int i = 0; i < BUFFER_SIZE; i++)
                pbuff->push_back(charBuff[i]);
        }
};
