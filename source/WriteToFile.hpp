#include "FileHandler.hpp"

class WriteToFile : public FileHandler {
    private:
        int outputBufferSize;
        std::ofstream file;
        char* charBuff;
    public:
        WriteToFile(std::queue<int>* pbuff, std::string fileName, int outputBufferSize) 
            : FileHandler(pbuff), outputBufferSize(outputBufferSize) {
                file.open(fileName, std::ios::out|std::ios::binary);
                charBuff = new char[outputBufferSize];
            }
        ~WriteToFile() {
            file.close();
        }

        void write() {
            for(int i = 0; i < outputBufferSize; i++) {
                charBuff[i] = pbuff->front();
                pbuff->pop();
            }

            file.write(charBuff, outputBufferSize);
            if(!file) {
                // char message[40];
                // sprintf(message, "Number of bytes read %ld\n", file.gcount());
                // std::cout << message << BUFFER_SIZE << std::endl;
                throw NotEnoughData();
            }
            // for(int i = 0; i < BUFFER_SIZE; i++)
            //     pbuff->push_back(charBuff[i]);
        }
};
