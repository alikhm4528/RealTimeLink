#ifndef WRITE_CHUNK_H
#define WRITE_CHUNK_H

#include "FileHandler.h"

class WriteChunk : public FileHandler {
    public:
        WriteChunk(std::queue<uint8_t>* buff, std::string fileName, size_t outputBufferSize);

        void write();
};
#endif
