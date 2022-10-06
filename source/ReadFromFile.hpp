#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1000_000
#endif

#include <vector>
#include <iostream>
#include <fstream>

class ReadFromFile {
    private:
        std::vector<int>* pbuff;
        const std::string fileName;
    public:
        ReadFromFile(std::vector<int>* pbuff) : pbuff(pbuff) {}
        
        void readDataFromFile(void) {
            char* memblock;
            std::streampos size;
            std::ifstream file(fileName, std::ios::in|std::ios::binary|std::ios::ate);

            if(file.is_open()) {
                size = file.tellg();
                memblock = new char [size];
                file.seekg(0, std::ios::beg);
                file.read(memblock, size);
                file.close();

                // cout << memblock;
                delete[] memblock;
            }
            else {
                // cout << "Unable to open file\n";
            }
        }
};