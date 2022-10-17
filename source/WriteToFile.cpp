#include "WriteToFile.h"

WriteToFile::WriteToFile(std::queue<uint8_t>* pbuff, std::string fileName, int outputBufferSize)
    : WriteChunk(pbuff, fileName, outputBufferSize) {}

void WriteToFile::write(ProcessData* ProcessObject) {
    while(!ProcessObject->isEndOfProcess() || !pbuff->empty()) {
        if(pbuff->size() == bufferSize){
            WriteChunk::write();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}