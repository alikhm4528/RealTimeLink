#define TEST_FILE "/home/alikhm/100G/project/RealTimeLink/Code Base/Database/test.bin"
#define EXCEPTION_FILE "/home/alikhm/100G/project/RealTimeLink/Code Base/Database/throwException.bin"
#define INPUT_FILE "/home/alikhm/100G/project/RealTimeLink/Code Base/Database/inputData.bin"

#include <gtest/gtest.h>
#include "ReadFromFile.hpp"

class ReadFromFileTests : public ::testing::Test {
    protected:
        std::queue<int>* buffer;
        ReadFromFile* ReadTread;

        void SetUp() override {
            buffer = new std::queue<int>();
        }

        void TearDown() override {
            delete buffer;
            if(ReadTread != nullptr)
                delete ReadTread;
        }
};

TEST_F(ReadFromFileTests, CorrectData6) {
    int anwser[] = {1, 0, 1, 0, 0, 1};

    ReadTread = new ReadFromFile(buffer, TEST_FILE, 6);
    ReadTread->read();

    ASSERT_EQ(6, buffer->size());

    for(int i = 0; i < 6; i++) {
        ASSERT_EQ(buffer->front(), anwser[i]);
        buffer->pop();
    }
}

TEST_F(ReadFromFileTests, ThrowExceptionNotEnoughData) {
    ReadTread = new ReadFromFile(buffer, EXCEPTION_FILE, 6);
    ASSERT_THROW({
        ReadTread->read();
    }, NotEnoughData);
}

TEST_F(ReadFromFileTests, NoThrowExceptionForInputData) {
    ReadTread = new ReadFromFile(buffer, INPUT_FILE, 1000000);

    ASSERT_NO_THROW({
        for(int i = 0; i < 10; i++) {
            ReadTread->read();
        }
    });
}