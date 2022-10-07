#ifndef FILE_HANDLER_HPP
#define FILE_HANDLER_HPP

#include <queue>
#include <iostream>
#include <fstream>

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
        std::queue<int>* pbuff;
        std::fstream file;
        char* charBuff;
        int bufferSize;
    public:
        FileHandler(std::queue<int>* pbuff, int bufferSize) 
        : pbuff(pbuff), bufferSize(bufferSize) {
            charBuff = new char [bufferSize];
        }
        ~FileHandler() {
            if(file.is_open())
                file.close();
        }
};
#endif