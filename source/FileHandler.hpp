#ifndef FILE_HANDLER_HPP
#define FILE_HANDLER_HPP

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1000000
#endif

#include <deque>
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
        std::deque<int>* pbuff;
    public:
        FileHandler(std::deque<int>* pbuff) : pbuff(pbuff) {}
};
#endif