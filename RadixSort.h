#pragma once

#include "BinFileGenerator.h"

class RadixSort
{
public:
    RadixSort(bin_file::IFile* file);
    ~RadixSort();

    void sort();

private:
    bin_file::IFile* file_;
    bin_file::IFile* fileTmp_;

    static const std::uint16_t K = 256;
    static const std::uint8_t D = 2;
    std::uint32_t index_[K];
};
