#include "QuickSort.h"
#include "BinFileGenerator.h"

#include <gtest/gtest.h>

TEST(QuickSortTest, Sort)
{
    bin_file::DataType arr[] = { 35750, 627, 9194, 60530, 50869, 1803, 17137, 17137, 2222, 56860 };

    QuickSort<bin_file::DataType> quick(arr, 10);

    std::cerr << "result: " << std::endl;
    for (int i = 0; i < 10; ++i) {
        std::cerr << arr[i] << " ";
    }
    std::cerr << std::endl;
}
