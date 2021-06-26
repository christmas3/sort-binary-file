#include "BinFileGenerator.h"

#include <gtest/gtest.h>

static size_t kNumberCount = 100000000;

TEST(BinFileGenerator, RandomGenerate)
{
    bin_file::RandomGenerator fileGen("./numbers.bin", kNumberCount);
}

TEST(BinFileGenerator, RandomGenerateDebug)
{
    bin_file::RandomGenerator fileGen("./numbers.bin", 10);

    fileGen.seek(0);
    bin_file::DataType data;
    std::vector<bin_file::DataType> vec;
    vec.reserve(kNumberCount);
    std::cerr << "data: " << std::endl;
    while (fileGen.read(data)) {
        std::cerr << data << " ";
        vec.push_back(data);
    }
    std::cerr << std::endl;

    for (auto i = 0; i < kNumberCount; ++i) {
        fileGen.read(i, data);
        ASSERT_EQ(vec[i], data);
    }
}

TEST(BinFileGenerator, ReadBuf)
{
    bin_file::RandomGenerator fileGen("./numbers.bin", 10);

    bin_file::DataType buf[5];
    fileGen.read(5, buf, 5);

    for (int i = 0; i < 5; ++i) {
        std::cerr << "buf[i]: " << buf[i] << std::endl;
    }
}

TEST(BinFileGenerator, ReadRevers)
{
    bin_file::RandomGenerator fileGen("./numbers.bin", kNumberCount);

    bin_file::DataType data;
    while (fileGen.readRevers(data)) {
        std::cerr << data << " ";
    }
}

TEST(BinFileGenerator, ZeroGenerator)
{
    bin_file::ZeroGenerator fileGen("./numbers.bin", kNumberCount);

    fileGen.seek(0);
    bin_file::DataType data;
    while (fileGen.read(data)) {
        std::cerr << data << " ";
    }
}
