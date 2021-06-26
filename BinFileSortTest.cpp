#include "BinFileGenerator.h"
#include "CombinedSort.h"
#include "RadixSort.h"

#include <gtest/gtest.h>

#define TimeLapse(code, time)                             \
    {                                                     \
        auto begin_t = std::clock();                      \
        code;                                             \
        auto end_t = std::clock();                        \
        time = (float)(end_t - begin_t) / CLOCKS_PER_SEC; \
    }

static const size_t kNumbersE7 = 10000000;
static const size_t kNumbersE8 = 100000000;

TEST(BinFileSortTest, MergeSort)
{
    bin_file::RandomGenerator fileGen("./numbers.bin", kNumbersE7);

    MergeSort mergeSort(&fileGen);

    double time = 0;
    TimeLapse(mergeSort.sort(), time);
    std::cerr << "time: " << time << std::endl;
}

TEST(BinFileSortTest, CombinedSort)
{
    bin_file::RandomGenerator fileGen("./numbers.bin", kNumbersE7);

    CombinedSort combinedSort(&fileGen);

    double time = 0;
    TimeLapse(combinedSort.sort(), time);
    std::cerr << "time: " << time << std::endl;
}

TEST(BinFileSortTest, RadixSortE7)
{
    bin_file::RandomGenerator fileGen("./numbers.bin", kNumbersE7);

    RadixSort radixSort(&fileGen);

    double time = 0;
    TimeLapse(radixSort.sort(), time);
    std::cerr << "time: " << time << std::endl;
}

TEST(BinFileSortTest, RadixSortE8)
{
    bin_file::RandomGenerator fileGen("./numbers.bin", kNumbersE8);

    RadixSort radixSort(&fileGen);

    double time = 0;
    TimeLapse(radixSort.sort(), time);
    std::cerr << "time: " << time << std::endl;
}
