#include <thread>
#include "ReadChunk.h"

class ReadFromFile : public ReadChunk {
    public:
        ReadFromFile(std::queue<uint8_t>* buff
            , std::string fileName
            , size_t bufferSize);

        void read();
};