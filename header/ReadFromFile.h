#ifndef READ_FROM_FILE_H
#define READ_FROM_FILE_H

#include <thread>
#include <queue>
#include "ReadChunk.h"

class ReadFromFile : public ReadChunk {
    public:
        ReadFromFile(std::queue<uint8_t>* buff, std::string fileName, int bufferSize);

        void read();
};
#endif