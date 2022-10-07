#include "FileHandler.hpp"

class WriteToFile : public FileHandler {
    private:
        std::ofstream file;
        char* charBuff;
    public:
        WriteToFile(std::queue<int>* pbuff, std::string fileName, int outputBufferSize) 
            : FileHandler(pbuff, outputBufferSize) {
                file.open(fileName, std::ios::out|std::ios::binary);
                charBuff = new char[outputBufferSize];
            }
        ~WriteToFile() {
            file.close();
        }

        void write() {
            for(int i = 0; i < bufferSize; i++) {
                charBuff[i] = pbuff->front();
                pbuff->pop();
            }

            file.write(charBuff, bufferSize);
            if(!file) {
                // char message[40];
                // sprintf(message, "Number of bytes read %ld\n", file.gcount());
                // std::cout << message << BUFFER_SIZE << std::endl;
                throw NotEnoughData();
            }
        }
};
