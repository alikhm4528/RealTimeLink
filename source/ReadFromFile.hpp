#include "FileHandler.hpp"

class ReadFromFile : public FileHandler {
    public:
        ReadFromFile(std::queue<int>* pbuff, std::string fileName, int bufferSize) 
            : FileHandler(pbuff, bufferSize) {
                file.open(fileName, std::ios::in|std::ios::binary);
            }

        void read(void) {
            file.read(charBuff, bufferSize);
            if(!file) {
                char message[40];
                sprintf(message, "Number of bytes read %ld\n", file.gcount());
                // std::cout << message << BUFFER_SIZE << std::endl;
                throw NotEnoughData(message);
            }
            for(int i = 0; i < bufferSize; i++) { 
                pbuff->push(charBuff[i]);
            }
        }
};
