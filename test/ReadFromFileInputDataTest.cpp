#define INPUT_FILE "/home/alikhm/100G/project/RealTimeLink/Code Base/Database/inputData.bin"

#include <gtest/gtest.h>
#include "ReadFromFile.hpp"

std::deque<int> buffer;

TEST(ReadFromFileTests, NoThrowExceptionForInputData) {
    ReadFromFile ReadTread(&buffer, INPUT_FILE);
    ASSERT_NO_THROW({
        for(int i = 0; i < 10; i++) {
            ReadTread.read();
        }
    });
}