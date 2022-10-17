#ifndef READ_FROM_FILE_HPP
#define READ_FROM_FILE_HPP

#include <thread>
#include <queue>
#include "ReadChunk.hpp"

class ReadFromFile : public ReadChunk {
    public:
        ReadFromFile(std::queue<uint8_t>* pbuff, std::string fileName, int bufferSize)
            : ReadChunk(pbuff, fileName, bufferSize) {}

        void read() {
            while(!isEndOfRead()) {
                auto oneSecond = std::chrono::steady_clock::now() + std::chrono::seconds(1);
                ReadChunk::read();
                std::this_thread::sleep_until(oneSecond);
            }
        }
};
#endif
