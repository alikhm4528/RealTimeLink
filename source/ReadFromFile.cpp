#include "ReadFromFile.h"

ReadFromFile::ReadFromFile(std::queue<uint8_t>* buff, std::string fileName, size_t bufferSize)
    : ReadChunk(buff, fileName, bufferSize) {}

void ReadFromFile::read() {
    while(!isEndOfRead()) {
        auto oneSecond = std::chrono::steady_clock::now() + std::chrono::seconds(1);
        ReadChunk::read();
        std::this_thread::sleep_until(oneSecond);
    }
}
