#include "FileHandler.h"

FileHandler::FileHandler(std::queue<uint8_t>* pbuff, int bufferSize) 
    : pbuff(pbuff)
    , bufferSize(bufferSize)
     {
        charBuff = new char [bufferSize];
}

FileHandler::~FileHandler() {
    if(file.is_open())
        file.close();
}
