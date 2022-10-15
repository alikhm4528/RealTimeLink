#include <thread>
#include <queue>
#include "WriteChunk.hpp"
#include "ProcessData.hpp"

class WriteToFile : public WriteChunk {
    public:
        WriteToFile(std::queue<int>* pbuff, std::string fileName, int outputBufferSize)
            : WriteChunk(pbuff, fileName, outputBufferSize) {}

        void write(ProcessData* ProcessObject) {
            while(!ProcessObject->isEndOfProcess() || !pbuff->empty()) {
                if(pbuff->size() == bufferSize)
                    WriteChunk::write();
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
            }
        }
};