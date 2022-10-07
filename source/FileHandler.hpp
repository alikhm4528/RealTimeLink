#ifndef FILE_HANDLER_HPP
#define FILE_HANDLER_HPP

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1000000
#endif

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
    public:
        FileHandler(std::queue<int>* pbuff) : pbuff(pbuff) {}
};
#endif