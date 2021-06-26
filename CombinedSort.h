#pragma once

#include "BinFileGenerator.h"
#include "MergeSort.h"

class CombinedSort : public MergeSort
{
public:
    explicit CombinedSort(bin_file::IFile* file)
        : MergeSort(file)
    {
    }

protected:
    void merge(const std::int64_t l, const std::int64_t m, const std::int64_t r) override;

private:
    bin_file::DataType buf_[1024];
};
