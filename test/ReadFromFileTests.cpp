#define TEST_FILE "/home/alikhm/100G/project/RealTimeLink/Code Base/Database/test.bin"
#define EXCEPTION_FILE "/home/alikhm/100G/project/RealTimeLink/Code Base/Database/throwException.bin"

#include <gtest/gtest.h>
#include "ReadFromFile.hpp"

std::queue<int> buffer;

TEST(ReadFromFileTests, CorrectData6) {
    int anwser[] = {1, 0, 1, 0, 0, 1};

    ReadFromFile ReadTread(&buffer, TEST_FILE);
    ReadTread.read();

    ASSERT_EQ(6, buffer.size());

    for(int i = 0; i < 6; i++) {
        ASSERT_EQ(buffer.front(), anwser[i]);
        buffer.pop();
    }
}

TEST(ReadFromFileTests, ThrowExceptionNotEnoughData) {
    ReadFromFile ReadTread(&buffer, EXCEPTION_FILE);
    ASSERT_THROW({
        ReadTread.read();
    }, NotEnoughData);
}