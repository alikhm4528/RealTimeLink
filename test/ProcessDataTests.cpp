#include <gtest/gtest.h>
#include <deque>
#include "Hamming.hpp"
#include "Interleaving.hpp"

class ProcessDataTests : public ::testing::Test {
    protected:
        std::deque<int>* inputBuffer;
        std::deque<int>* outputBuffer;
        ProcessData* interleaving;
        ProcessData* hamming;

        void SetUp() override {
            inputBuffer = new std::deque<int>();
            outputBuffer = new std::deque<int>();
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
    inputBuffer->insert(inputBuffer->end()
        , { 1,  2,  3,  4,  5,
            6,  7,  8,  9,  10,
            11, 12, 13, 14, 15,
            16, 17, 18, 19, 20});
    interleaving->run(inputBuffer->begin());

    ASSERT_EQ(20, outputBuffer->size());

    int ind = 0;
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 4; j++) {
            ASSERT_EQ(j * 5 + i + 1, (*outputBuffer)[ind++]);
        }
    }
}

TEST_F(ProcessDataTests, InputDataSize4Hamming) {
    inputBuffer->insert(inputBuffer->end()
        , { 1,  2,  3,  4});
    hamming->run(inputBuffer->begin());

    ASSERT_EQ(7, outputBuffer->size());

    ASSERT_EQ(1, (*outputBuffer)[0]);
    ASSERT_EQ(2, (*outputBuffer)[1]);
    ASSERT_EQ(3, (*outputBuffer)[2]);
    ASSERT_EQ(4, (*outputBuffer)[3]);
    ASSERT_EQ(6, (*outputBuffer)[4]);
    ASSERT_EQ(9, (*outputBuffer)[5]);
    ASSERT_EQ(8, (*outputBuffer)[6]);
}