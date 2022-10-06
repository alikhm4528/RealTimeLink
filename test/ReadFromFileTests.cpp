#define FILE_NAME "/home/alikhm/100G/project/RealTimeLink/Code Base/Database/test.bin"

#include <gtest/gtest.h>
#include "ReadFromFile.hpp"

std::vector<int> buffer;

TEST(ReadFromFileTests, CorrectData6) {
    int anwser[] = {1, 0, 1, 0, 0, 1};

    ReadFromFile ReadTread(&buffer, FILE_NAME);
    ReadTread.readDataFromFile();

    for(int i = 0; i < 6; i++) {
        ASSERT_EQ(buffer[i], anwser[i]);
    }
}