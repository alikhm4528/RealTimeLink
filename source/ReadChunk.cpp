#include "ReadChunk.h"

ReadChunk::ReadChunk(std::queue<uint8_t>* buff
    , std::string fileName
    , size_t bufferSize) 
        : FileHandler(buff, bufferSize)
{
    file.open(fileName, std::ios::in|std::ios::binary);
    setEndPos();
}

void ReadChunk::read(void) {
    file.read(charBuff, bufferSize);
    if(!file) {
        throw NotEnoughData(makeExceptionMessage());
    }
    for(size_t i = 0; i < bufferSize; i++) {
        buff->push(charBuff[i]);
    }
}

bool ReadChunk::isEndOfRead() {
    return file.tellg() == endPos;
}

void ReadChunk::setEndPos() {
    file.seekg(0, std::ios::end);
    endPos = file.tellg();
    file.seekg(0, std::ios::beg);
}

char* ReadChunk::makeExceptionMessage() {
    char* message = new char[40];
    sprintf(message, "Number of bytes read %ld\n", file.gcount());
    return message;
}