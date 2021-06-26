#include "RadixSort.h"

RadixSort::RadixSort(bin_file::IFile* file)
    : file_(file)
    , fileTmp_(new bin_file::ZeroGenerator(file_->path() + ".tmp", file_->size()))
{
}

RadixSort::~RadixSort()
{
    delete fileTmp_;
}

static inline std::uint8_t getOctet(bin_file::DataType number, std::uint8_t count)
{
    return (number >> 4 * count) & 0x0F;
}

static inline std::uint8_t getByte(bin_file::DataType number, std::uint8_t count)
{
    return (number >> 8 * count) & 0xFF;
}

void RadixSort::sort()
{
    for (auto d = 0; d < D; ++d) {
        std::fill(index_, index_ + K, 0);
        file_->seek(0);
        bin_file::DataType number;
        while (file_->read(number)) {
            auto digit = getByte(number, d);
            ++index_[digit];
        }
        for (auto i = 1; i < K; ++i) {
            index_[i] += index_[i - 1];
        }
        file_->seek(0);
        while (file_->readRevers(number)) {
            auto digit = getByte(number, d);
            fileTmp_->seek(--index_[digit]);
            fileTmp_->write(number);
        }
        auto* tmp = file_;
        file_ = fileTmp_;
        fileTmp_ = tmp;
    }
}
