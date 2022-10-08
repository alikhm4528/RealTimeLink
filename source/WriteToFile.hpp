#include "FileHandler.hpp"

class WriteToFile : public FileHandler {
    public:
        WriteToFile(std::queue<int>* pbuff, std::string fileName, int outputBufferSize) 
            : FileHandler(pbuff, outputBufferSize) {
                file.open(fileName, std::ios::out|std::ios::binary);
                charBuff = new char[outputBufferSize];
            }

        void write() {
            for(int i = 0; i < bufferSize; i++) {
                charBuff[i] = pbuff->front();
                pbuff->pop();
            }

            file.write(charBuff, bufferSize);
            if(!file) {
                throw NotEnoughData("Can't write data");
            }
        }
};
