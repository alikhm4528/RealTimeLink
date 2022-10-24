#ifndef READ_CHUNK_H
#define READ_CHUNK_H

#include "FileHandler.h"

class ReadChunk : public FileHandler {
    private:
        size_t endPos;
    public:
        ReadChunk(std::queue<uint8_t>* buff
            , std::string fileName
            , size_t bufferSize);

        void read();
        bool isEndOfRead();
    private:
        void setEndPos();
        char* makeExceptionMessage();
};
#endif
