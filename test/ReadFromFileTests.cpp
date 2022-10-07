#define TEST_FILE "/home/alikhm/100G/project/RealTimeLink/Code Base/Database/test.bin"
#define EXCEPTION_FILE "/home/alikhm/100G/project/RealTimeLink/Code Base/Database/throwException.bin"
#define INPUT_FILE "/home/alikhm/100G/project/RealTimeLink/Code Base/Database/inputData.bin"

#include <gtest/gtest.h>
#include "ReadFromFile.hpp"

class ReadFromFileTests : public ::testing::Test {
    protected:
        std::queue<int>* buffer;
        ReadFromFile* ReadThread;

        void SetUp() override {
            buffer = new std::queue<int>();
        }

        void TearDown() override {
            delete buffer;
            if(ReadThread != nullptr)
                delete ReadThread;
        }
};

TEST_F(ReadFromFileTests, CorrectData6) {
    int anwser[] = {1, 0, 1, 0, 0, 1};

    ReadThread = new ReadFromFile(buffer, TEST_FILE, 6);
    ReadThread->read();

    ASSERT_EQ(6, buffer->size());

    for(int i = 0; i < 6; i++) {
        ASSERT_EQ(buffer->front(), anwser[i]);
        buffer->pop();
    }
}

TEST_F(ReadFromFileTests, ThrowExceptionNotEnoughData) {
    ReadThread = new ReadFromFile(buffer, EXCEPTION_FILE, 6);
    ASSERT_THROW({
        ReadThread->read();
    }, NotEnoughData);
}

TEST_F(ReadFromFileTests, NoThrowExceptionForInputData) {
    ReadThread = new ReadFromFile(buffer, INPUT_FILE, 1000000);

    ASSERT_NO_THROW({
        for(int i = 0; i < 10; i++) {
            ReadThread->read();
        }
    });
}