#include "WriteToFile.h"

WriteToFile::WriteToFile(std::queue<uint8_t>* buff, std::string fileName, int outputBufferSize)
    : WriteChunk(buff, fileName, outputBufferSize) {}

void WriteToFile::write() {
    uint8_t cnt = 0;
    while(cnt < 25) {
        cnt++;
        if(buff->size() == bufferSize){
            WriteChunk::write();
            cnt = 0;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}