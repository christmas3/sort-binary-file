#include "CombinedSort.h"
#include "QuickSort.h"

#include <iostream>

void CombinedSort::merge(const std::int64_t l, const std::int64_t m, const std::int64_t r)
{
    auto size = r - l + 1;
    if (size > 1024) {
        MergeSort::merge(l, m, r);
        return;
    }

    if (!getFile()->read(l, buf_, size)) {
        std::cerr << "error read from file in pos: " << l << " size: " << size << std::endl;
        exit(1);
    }

    QuickSort<bin_file::DataType>(buf_, size);

    getFile()->seek(l);
    for (int i = 0; i < size; ++i) {
        getFile()->write(buf_[i]);
    }
}
