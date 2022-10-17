#define INTERLEAVING_TEST_FILE "/home/alikhm/100G/project/RealTimeLink/RealTimeLink/Database/interleavingTest.bin"
#define HAMMING_TEST_FILE "/home/alikhm/100G/project/RealTimeLink/RealTimeLink/Database/hammingTest.bin"

#include <gtest/gtest.h>
#include <queue>
#include "Hamming.hpp"
#include "Interleaving.hpp"
#include "ReadFromFile.hpp"

class ProcessDataTests : public ::testing::Test {
    protected:
        std::queue<int>* inputBuffer;
        std::queue<int>* outputBuffer;
        ReadFromFile* ReadObjectInterleaving;
        ReadFromFile* ReadObjectHamming;
        ProcessData* interleaving;
        ProcessData* hamming;

        void SetUp() override {
            inputBuffer = new std::queue<int>();
            outputBuffer = new std::queue<int>();
            ReadObjectInterleaving = new ReadFromFile(inputBuffer, INTERLEAVING_TEST_FILE, 20);
            ReadObjectHamming = new ReadFromFile(inputBuffer, HAMMING_TEST_FILE, 4);
            interleaving = new Interleaving(inputBuffer, outputBuffer, ReadObjectInterleaving, 20);
            hamming = new Hamming(inputBuffer, outputBuffer, ReadObjectHamming, 4);
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