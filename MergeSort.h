#pragma once

#include <cstdint>

namespace bin_file {
class IFile;
};

class MergeSort
{
public:
    explicit MergeSort(bin_file::IFile* file);
    ~MergeSort();

    void sort();

    MergeSort(const MergeSort&) = delete;
    MergeSort& operator=(const MergeSort&) = delete;

protected:
    virtual void merge(const std::int64_t l, const std::int64_t m, const std::int64_t r);

    bin_file::IFile* getFile() { return file_; }

private:
    void sortImpl(const std::int64_t l, const std::int64_t r);

    bin_file::IFile* file_;
    bin_file::IFile* tmpFile_;
};
