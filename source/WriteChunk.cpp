#include "WriteChunk.h"

WriteChunk::WriteChunk(std::queue<uint8_t>* buff, std::string fileName, int outputBufferSize) 
    : FileHandler(buff, outputBufferSize) {

    file.open(fileName, std::ios::out|std::ios::binary);
    charBuff = new char[outputBufferSize];
}

void WriteChunk::write() {
    for(int i = 0; i < bufferSize; i++) {
        charBuff[i] = buff->front();
        buff->pop();
    }

    file.write(charBuff, bufferSize);
    if(!file) {
        throw NotEnoughData("Can't write data");
    }
}