#ifndef READ_CHUNK_H
#define READ_CHUNK_H

#include <queue>
#include <cstdint>
#include "FileHandler.h"

class ReadChunk : public FileHandler {
    private:
        long long endPos;
    public:
        ReadChunk(std::queue<uint8_t>* pbuff, std::string fileName, int bufferSize);

        void read();
        bool isEndOfRead();
};
#endif
