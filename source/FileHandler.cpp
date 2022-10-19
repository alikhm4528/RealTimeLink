#include "FileHandler.h"

FileHandler::FileHandler(std::queue<uint8_t>* buff, int bufferSize) 
    : buff(buff)
    , bufferSize(bufferSize)
     {
        charBuff = new char [bufferSize];
}

FileHandler::~FileHandler() {
    if(file.is_open())
        file.close();
}

void FileHandler::closeFile() {
    if(file.is_open())
        file.close();
}
