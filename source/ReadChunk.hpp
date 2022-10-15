#ifndef READ_CHUNK_HPP
#define READ_CHUNK_HPP

#include "FileHandler.hpp"

class ReadChunk : public FileHandler {
    private:
        long long endPos;
    public:
        ReadChunk(std::queue<int>* pbuff, std::string fileName, int bufferSize) 
            : FileHandler(pbuff, bufferSize) {
                file.open(fileName, std::ios::in|std::ios::binary);
                file.seekg(0, std::ios::end);
                endPos = file.tellg();
                file.seekg(0, std::ios::beg);
            }

        void read(void) {
            file.read(charBuff, bufferSize);
            if(!file) {
                char message[40];
                sprintf(message, "Number of bytes read %ld\n", file.gcount());
                throw NotEnoughData(message);
            }
            for(int i = 0; i < bufferSize; i++) { 
                pbuff->push(charBuff[i]);
            }
        }

        bool isEndOfRead() {
            return file.tellg() == endPos;
        }
};
#endif
