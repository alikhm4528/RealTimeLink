#define TEST_OUTPUT_FILE "/home/alikhm/100G/project/RealTimeLink/Code Base/Database/testOutput.bin"
#define INPUT_FILE "/home/alikhm/100G/project/RealTimeLink/Code Base/Database/inputData.bin"

#include <gtest/gtest.h>
#include <fstream>
#include "ReadFromFile.hpp"
#include "WriteToFile.hpp"

class WriteToFileTests : public ::testing::Test {
    protected:
        std::queue<int>* inputBuffer;
        std::queue<int>* outputBuffer;
        ReadFromFile* ReadThread;
        WriteToFile* WriteThread;

        void SetUp() override {
            inputBuffer = new std::queue<int>();
            outputBuffer = new std::queue<int>();
        }

        void TearDown() override {
            delete inputBuffer;
            delete outputBuffer;
            if(ReadThread != nullptr)
                delete ReadThread;
            if(WriteThread != nullptr)
                delete WriteThread;
        }
};

TEST_F(WriteToFileTests, CorrectData6) {
    for(int i = 0; i < 6; i++) {
        inputBuffer->push(i);
    }

    WriteThread = new WriteToFile(inputBuffer, TEST_OUTPUT_FILE, 6);
    WriteThread->write();

    delete WriteThread; // to close the file

    ReadThread = new ReadFromFile(outputBuffer, TEST_OUTPUT_FILE, 6);
    ReadThread->read();

    ASSERT_EQ(6, outputBuffer->size());

    for(int i = 0; i < 6; i++) {
        ASSERT_EQ(outputBuffer->front(), i);
        outputBuffer->pop();
    }
}

TEST_F(WriteToFileTests, EntireInputDataReadWrite) {
    ReadThread = new ReadFromFile(inputBuffer, INPUT_FILE, 1000000);
    for(int i = 0; i < 10; i++) {
        ReadThread->read();
    }

    delete ReadThread;

    WriteThread = new WriteToFile(inputBuffer, TEST_OUTPUT_FILE, 1000000);
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