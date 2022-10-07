#define TEST_FILE "/home/alikhm/100G/project/RealTimeLink/Code Base/Database/test.bin"
#define EXCEPTION_FILE "/home/alikhm/100G/project/RealTimeLink/Code Base/Database/throwException.bin"

#include <gtest/gtest.h>
#include "ReadFromFile.hpp"

std::vector<int> buffer;

TEST(ReadFromFileTests, CorrectData6) {
    int anwser[] = {1, 0, 1, 0, 0, 1};

    ReadFromFile ReadTread(&buffer, TEST_FILE);
    ReadTread.read();

    for(int i = 0; i < 6; i++) {
        ASSERT_EQ(buffer[i], anwser[i]);
    }
}

TEST(ReadFromFileTests, ThrowExceptionNotEnoughData) {
    ReadFromFile ReadTread(&buffer, EXCEPTION_FILE);
    ASSERT_THROW({
        ReadTread.read();
    }, NotEnoughData);
}