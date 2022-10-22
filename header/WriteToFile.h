#include <thread>
#include "WriteChunk.h"

class WriteToFile : public WriteChunk {
    public:
        WriteToFile(std::queue<uint8_t>* buff, std::string fileName, size_t outputBufferSize);
        
        void write();
};