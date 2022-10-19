#define TEST_OUTPUT_FILE "/home/alikhm/project/RealTimeLink/Database/testOutput.bin"
#define INPUT_FILE "/home/alikhm/project/RealTimeLink/Database/inputData.bin"

#include <gtest/gtest.h>
#include <fstream>
#include "ReadChunk.h"
#include "WriteChunk.h"

class WriteChunkTests : public ::testing::Test {
    protected:
        std::queue<uint8_t>* inputBuffer;
        std::queue<uint8_t>* outputBuffer;
        ReadChunk* ReadThread;
        WriteChunk* WriteThread;

        void SetUp() override {
            inputBuffer = new std::queue<uint8_t>();
            outputBuffer = new std::queue<uint8_t>();
        }

        void TearDown() override {
            delete inputBuffer;
            delete outputBuffer;
        }
};

TEST_F(WriteChunkTests, CorrectData6) {
    for(int i = 0; i < 6; i++) {
        inputBuffer->push(i);
    }

    WriteThread = new WriteChunk(inputBuffer, TEST_OUTPUT_FILE, 6);
    WriteThread->write();

    delete WriteThread; // to close the file

    ReadThread = new ReadChunk(outputBuffer, TEST_OUTPUT_FILE, 6);
    ReadThread->read();

    delete ReadThread;

    ASSERT_EQ(6, outputBuffer->size());

    for(int i = 0; i < 6; i++) {
        ASSERT_EQ(outputBuffer->front(), i);
        outputBuffer->pop();
    }
}

TEST_F(WriteChunkTests, EntireInputDataReadWrite) {
    ReadThread = new ReadChunk(inputBuffer, INPUT_FILE, 1000000);
    for(int i = 0; i < 10; i++) {
        ReadThread->read();
    }

    delete ReadThread;

    WriteThread = new WriteChunk(inputBuffer, TEST_OUTPUT_FILE, 1000000);
    for(int i = 0; i < 10; i++) {
        WriteThread->write();
    }

    delete WriteThread;

    std::ifstream f1(INPUT_FILE, std::ifstream::binary|std::ifstream::ate);
    std::ifstream f2(TEST_OUTPUT_FILE, std::ifstream::binary|std::ifstream::ate);

    if (f1.fail() || f2.fail()) {
        FAIL();
    }

    ASSERT_EQ(f1.tellg(), f2.tellg());

    //seek back to beginning and use std::equal to compare contents
    f1.seekg(0, std::ifstream::beg);
    f2.seekg(0, std::ifstream::beg);
    ASSERT_TRUE(std::equal(std::istreambuf_iterator<char>(f1.rdbuf()),
                      std::istreambuf_iterator<char>(),
                      std::istreambuf_iterator<char>(f2.rdbuf())));
}
