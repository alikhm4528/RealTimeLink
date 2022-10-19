#include "ReadFromFile.h"

ReadFromFile::ReadFromFile(std::queue<uint8_t>* pbuff, std::string fileName, int bufferSize)
    : ReadChunk(pbuff, fileName, bufferSize) {}

void ReadFromFile::read() {
    while(!isEndOfRead()) {
        auto oneSecond = std::chrono::steady_clock::now() + std::chrono::seconds(1);
        ReadChunk::read();
        std::this_thread::sleep_until(oneSecond);
    }
}