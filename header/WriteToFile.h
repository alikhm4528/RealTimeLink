#include <thread>
#include <queue>
#include "WriteChunk.h"
#include "ProcessData.h"

class WriteToFile : public WriteChunk {
    public:
        WriteToFile(std::queue<uint8_t>* buff, std::string fileName, int outputBufferSize);
        
        void write();
};