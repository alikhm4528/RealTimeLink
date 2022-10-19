#ifndef PREFIX
#define PREFIX "/home/alikhm/100G/project/RealTimeLink/RealTimeLink/Database/"
#endif

#define getAddress(file) (std::string)PREFIX + file

#include <gtest/gtest.h>
#include "ReadChunk.h"

class ReadChunkTests : public ::testing::Test {
    protected:
        std::queue<uint8_t>* buffer;
        ReadChunk* ReadThread;

        void SetUp() override {
            buffer = new std::queue<uint8_t>();
        }

        void TearDown() override {
            delete buffer;
            if(ReadThread != nullptr)
                delete ReadThread;
        }
};

TEST_F(ReadChunkTests, CorrectData6) {
    int anwser[] = {1, 0, 1, 0, 0, 1};

    ReadThread = new ReadChunk(buffer, getAddress("test.bin"), 6);
    ReadThread->read();

    ASSERT_EQ(6, buffer->size());

    for(int i = 0; i < 6; i++) {
        ASSERT_EQ(buffer->front(), anwser[i]);
        buffer->pop();
    }
}

TEST_F(ReadChunkTests, ThrowExceptionNotEnoughData) {
    ReadThread = new ReadChunk(buffer
        , getAddress("throwException.bin"), 6);
    ASSERT_THROW({
        ReadThread->read();
    }, NotEnoughData);
}

TEST_F(ReadChunkTests, NoThrowExceptionForInputData) {
    ReadThread = new ReadChunk(buffer
        , getAddress("inputData.bin"), 1000000);

    ASSERT_NO_THROW({
        for(int i = 0; i < 10; i++) {
            ReadThread->read();
        }
    });
}