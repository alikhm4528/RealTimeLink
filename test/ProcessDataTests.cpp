#include <gtest/gtest.h>
#include <queue>
#include "Hamming.hpp"
#include "Interleaving.hpp"

class ProcessDataTests : public ::testing::Test {
    protected:
        std::queue<int>* inputBuffer;
        std::queue<int>* outputBuffer;
        ProcessData* interleaving;
        ProcessData* hamming;

        void SetUp() override {
            inputBuffer = new std::queue<int>();
            outputBuffer = new std::queue<int>();
            interleaving = new Interleaving(inputBuffer, outputBuffer);
            hamming = new Hamming(inputBuffer, outputBuffer);
        }

        void TearDown() override {
            delete inputBuffer;
            delete outputBuffer;
            delete interleaving;
            delete hamming;
        }
};

TEST_F(ProcessDataTests, InputDataSize20Interleaving) {
    for(int i = 0; i < 20; i++) {
        inputBuffer->push(i + 1);
    }

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
    for(int i = 0; i < 4; i++) {
        inputBuffer->push(i + 1);
    }
    hamming->run();

    ASSERT_EQ(7, outputBuffer->size());

    int anwser[] = {1, 2, 3, 4, 6, 9, 8};

    for(int i = 0; i < 7; i++) {
        ASSERT_EQ(anwser[i], outputBuffer->front());
        outputBuffer->pop();
    }
}