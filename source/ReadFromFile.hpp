#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1000000
#endif

#include <vector>
#include <iostream>
#include <fstream>

class NotEnoughData : public std::exception {
    private:
        const char* message;
    public:
        NotEnoughData(const char* message) : message(message) {}

        virtual const char *what() const noexcept {
            return message;
        }
};

class ReadFromFile {
    private:
        std::vector<int>* pbuff;
        std::ifstream file;
    public:
        ReadFromFile(std::vector<int>* pbuff, std::string fileName) 
            : pbuff(pbuff) {
                file.open(fileName, std::ios::in|std::ios::binary);
            }
        ~ReadFromFile() {
            file.close();
        }

        void readDataFromFile(void) {
            char charBuff[BUFFER_SIZE];

            file.read(charBuff, BUFFER_SIZE);
            if(!file) {
                char message[40];
                sprintf(message, "Number of bytes read %ld\n", file.gcount());
                std::cout << message << BUFFER_SIZE << std::endl;
                throw NotEnoughData(message);
            }
            for(int i = 0; i < BUFFER_SIZE; i++)
                pbuff->push_back(charBuff[i]);
        }
};
