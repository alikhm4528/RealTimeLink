#ifndef READ_FROM_FILE_HPP
#define READ_FROM_FILE_HPP

#include <thread>
#include <queue>
#include "ReadChunk.hpp"

class ReadFromFile : public ReadChunk {
    public:
        ReadFromFile(std::queue<int>* pbuff, std::string fileName, int bufferSize)
            : ReadChunk(pbuff, fileName, bufferSize) {}

        void read() {
            while(!isEndOfRead()) {
                ReadChunk::read();
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
        }
};
#endif
