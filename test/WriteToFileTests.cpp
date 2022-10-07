#define TEST_OUTPUT_FILE "/home/alikhm/100G/project/RealTimeLink/Code Base/Database/testOutput.bin"

#include <gtest/gtest.h>
#include "ReadFromFile.hpp"
#include "WriteToFile.hpp"

std::queue<int> buffer;

TEST(ReadFromFileTests, CorrectData6) {
    for(int i = 0; i < 6; i++) {
        buffer.push(i);
    }

    WriteToFile WriteTread(&buffer, TEST_OUTPUT_FILE, 6);
    WriteTread.write();

    ReadFromFile ReadTread(&buffer, TEST_OUTPUT_FILE, 6);
    ReadTread.read();

    ASSERT_EQ(6, buffer.size());

    for(int i = 0; i < 6; i++) {
        ASSERT_EQ(buffer.front(), anwser[i]);
        buffer.pop();
    }
}