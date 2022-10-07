#include "FileHandler.hpp"

class ReadFromFile : public FileHandler {
    private:
        std::ifstream file;
    public:
        ReadFromFile(std::vector<int>* pbuff, std::string fileName) 
            : FileHandler(pbuff) {
                file.open(fileName, std::ios::in|std::ios::binary);
            }
        ~ReadFromFile() {
            file.close();
        }

        void read(void) {
            char charBuff[BUFFER_SIZE];

            file.read(charBuff, BUFFER_SIZE);
            if(!file) {
                char message[40];
                sprintf(message, "Number of bytes read %ld\n", file.gcount());
                // std::cout << message << BUFFER_SIZE << std::endl;
                throw NotEnoughData(message);
            }
            for(int i = 0; i < BUFFER_SIZE; i++)
                pbuff->push_back(charBuff[i]);
        }
};
