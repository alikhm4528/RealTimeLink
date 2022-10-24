#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H
#include <fstream>
#include <queue>
#include <cstdint>

class NotEnoughData : public std::exception {
    private:
        const char* message;
    public:
        NotEnoughData() : message("") {}
        NotEnoughData(const char* message) : message(message) {}

        virtual const char *what() const noexcept {
            return message;
        }
};

class FileHandler {
    protected:
        std::queue<uint8_t>* buff;
        std::fstream file;
        char* charBuff;
        size_t bufferSize;
    public:
        FileHandler(std::queue<uint8_t>*, size_t);
        ~FileHandler();
        
        void closeFile();
};
#endif
