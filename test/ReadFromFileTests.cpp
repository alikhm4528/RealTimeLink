#define FILE_NAME "/home/alikhm/project/ReadTimeLink/'Code Base'/Database/test.bin"

#include <gtest/gtest.h>
#include "ReadFromFile.hpp"

std::vector<int> buffer;
const std::string FileName = "/home/alikhm/project/ReadTimeLink/'Code Base'/Database/test.bin";

TEST(ReadFromFileTests, CorrectData10) {
    int anwser[] = {1, 0, 1, 0, 1, 0, 1, 0, 1, 0};
    ReadFromFile ReadTread(&buffer);

    ReadTread.readDataFromFile();

    for(int i = 0; i < 10; i++) {
        ASSERT_EQ(buffer[i], anwser[i]);
    }
}