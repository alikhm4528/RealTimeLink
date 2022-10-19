#ifndef PREFIX
#define PREFIX "/home/alikhm/100G/project/RealTimeLink/RealTimeLink/Database/"
#endif

#define getAddress(file) (std::string)PREFIX + file

#include <gtest/gtest.h>
#include <queue>
#include "Hamming.h"
#include "Interleaving.h"
#include "ReadFromFile.h"

class ProcessDataTests : public ::testing::Test {
    protected:
        std::queue<uint8_t>* inputBuffer;
        std::queue<uint8_t>* outputBuffer;
        ReadFromFile* ReadObjectInterleaving;
        ReadFromFile* ReadObjectHamming;
        ProcessData* interleaving;
        ProcessData* hamming;

        void SetUp() override {
            inputBuffer = new std::queue<uint8_t>();
            outputBuffer = new std::queue<uint8_t>();
            ReadObjectInterleaving = new ReadFromFile(inputBuffer
                , getAddress("interleavingTest.bin"), 20);
            ReadObjectHamming = new ReadFromFile(inputBuffer
                , getAddress("hammingTest.bin"), 4);
            interleaving = new Interleaving(inputBuffer, outputBuffer, 20);
            hamming = new Hamming(inputBuffer, outputBuffer, 4);
        }

        void TearDown() override {
            delete inputBuffer;
            delete outputBuffer;
            delete interleaving;
            delete hamming;
        }
};

TEST_F(ProcessDataTests, InputDataSize20Interleaving) {
    ReadObjectInterleaving->read();
    interleaving->run();

    ASSERT_EQ(20, outputBuffer->size());

    int ind = 0;
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 4; j++) {
            ASSERT_EQ(j * 5 + i + 1, outputBuffer->front());
            outputBuffer->pop();
        }
    }
}

TEST_F(ProcessDataTests, InputDataSize4Hamming) {
    ReadObjectHamming->read();
    hamming->run();

    ASSERT_EQ(7, outputBuffer->size());

    int anwser[] = {1, 2, 3, 4, 6, 9, 8};

    for(int i = 0; i < 7; i++) {
        ASSERT_EQ(anwser[i], outputBuffer->front());
        outputBuffer->pop();
    }
}