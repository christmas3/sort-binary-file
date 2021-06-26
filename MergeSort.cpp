#include "MergeSort.h"
#include "BinFileGenerator.h"

#include <iostream>

MergeSort::MergeSort(bin_file::IFile* file)
    : file_(file)
    , tmpFile_(new bin_file::File(file_->path() + ".tmp"))
{
}

MergeSort::~MergeSort()
{
    delete tmpFile_;
}

void MergeSort::sort()
{
    sortImpl(0, file_->size() - 1);
}

void MergeSort::sortImpl(const std::int64_t l, const std::int64_t r)
{
    if (l >= r)
        return;

    auto m = (l + r) / 2;
    sortImpl(l, m);
    sortImpl(m + 1, r);
    merge(l, m, r);
}

bin_file::DataType readFromFile(std::int64_t pos, bin_file::IFile* file)
{
    bin_file::DataType val;
    if (!file->read(pos, val)) {
        std::cerr << "error read from file in pos: " << pos << std::endl;
        exit(1);
    }
    return val;
}

void MergeSort::merge(const std::int64_t l, const std::int64_t m, const std::int64_t r)
{
    tmpFile_->seek(0);
    std::int64_t a = l, b = m + 1;
    bin_file::DataType aVal = readFromFile(a, file_);
    bin_file::DataType bVal = readFromFile(b, file_);

    while (a <= m && b <= r) {
        if (aVal < bVal) {
            tmpFile_->write(aVal);
            if (++a > m) {
                break;
            }
            aVal = readFromFile(a, file_);
        }
        else {
            tmpFile_->write(bVal);
            if (++b > r) {
                break;
            }
            bVal = readFromFile(b, file_);
        }
    }
    while (a <= m) {
        tmpFile_->write(readFromFile(a++, file_));
    }
    while (b <= r) {
        tmpFile_->write(readFromFile(b++, file_));
    }

    file_->seek(l);
    tmpFile_->seek(0);
    for (std::int64_t i = l; i <= r; ++i) {
        file_->write(readFromFile(i - l, tmpFile_));
    }
}
