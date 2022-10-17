#include "ReadChunk.h"

ReadChunk::ReadChunk(std::queue<uint8_t>* pbuff, std::string fileName, int bufferSize) 
    : FileHandler(pbuff, bufferSize) {

    file.open(fileName, std::ios::in|std::ios::binary);
    file.seekg(0, std::ios::end);
    endPos = file.tellg();
    file.seekg(0, std::ios::beg);
}

void ReadChunk::read(void) {
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

bool ReadChunk::isEndOfRead() {
    return file.tellg() == endPos;
}