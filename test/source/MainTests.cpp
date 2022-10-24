#ifndef PREFIX
#define PREFIX "/home/alikhm/100G/project/RealTimeLink/RealTimeLink/Database/"
#endif

#define getAddress(file) (std::string)PREFIX + file

#include <gtest/gtest.h>
#include "Main.h"

class MainTests : public ::testing::Test {
    protected:
        Main* Program;

        void SetUp() override {
        }

        void TearDown() override {
        }
};

TEST_F(MainTests, Interleaving) {
    Program = new Main(INTERLEAVING);
    Program->run();

    std::ifstream f1(getAddress("interleaver.bin")
        , std::ifstream::binary|std::ifstream::ate);
    std::ifstream f2(getAddress("outputData.bin")
        , std::ifstream::binary|std::ifstream::ate);

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

TEST_F(MainTests, Hamming) {
    Program = new Main(HAMMING);
    Program->run();

    std::ifstream f1(getAddress("hamming.bin")
        , std::ifstream::binary|std::ifstream::ate);
    std::ifstream f2(getAddress("outputData.bin")
        , std::ifstream::binary|std::ifstream::ate);

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