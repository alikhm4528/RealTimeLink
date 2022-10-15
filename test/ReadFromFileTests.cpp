#define TEST_FILE "/home/alikhm/100G/project/RealTimeLink/RealTimeLink/Database/test.bin"
#define EXCEPTION_FILE "/home/alikhm/100G/project/RealTimeLink/RealTimeLink/Database/throwException.bin"
#define INPUT_FILE "/home/alikhm/100G/project/RealTimeLink/RealTimeLink/Database/inputData.bin"

#include <gtest/gtest.h>
#include "ReadChunk.hpp"

class ReadChunkTests : public ::testing::Test {
    protected:
        std::queue<int>* buffer;
        ReadChunk* ReadThread;

        void SetUp() override {
            buffer = new std::queue<int>();
        }

        void TearDown() override {
            delete buffer;
            if(ReadThread != nullptr)
                delete ReadThread;
        }
};

TEST_F(ReadChunkTests, CorrectData6) {
    int anwser[] = {1, 0, 1, 0, 0, 1};

    ReadThread = new ReadChunk(buffer, TEST_FILE, 6);
    ReadThread->read();

    ASSERT_EQ(6, buffer->size());

    for(int i = 0; i < 6; i++) {
        ASSERT_EQ(buffer->front(), anwser[i]);
        buffer->pop();
    }
}

TEST_F(ReadChunkTests, ThrowExceptionNotEnoughData) {
    ReadThread = new ReadChunk(buffer, EXCEPTION_FILE, 6);
    ASSERT_THROW({
        ReadThread->read();
    }, NotEnoughData);
}

TEST_F(ReadChunkTests, NoThrowExceptionForInputData) {
    ReadThread = new ReadChunk(buffer, INPUT_FILE, 1000000);

    ASSERT_NO_THROW({
        for(int i = 0; i < 10; i++) {
            ReadThread->read();
        }
    });
}