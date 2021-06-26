#include "BinFileGenerator.h"

#include <cstring>
#include <iostream>
#include <limits>
#include <random>

namespace bin_file {
File::File(const std::string& path)
    : path_(path)
    , reverseStatus_(STOP)
{
    file_.open(path.c_str(), std::ios::in | std::ios::out | std::ios::binary);
    if (!file_.is_open()) {
        file_.open(path.c_str(), std::ios::out | std::ios::binary);
        checkStatus();
        file_.close();
        file_.open(path.c_str(), std::ios::in | std::ios::out | std::ios::binary);
        checkStatus();
    }
}

void File::write(DataType data)
{
    file_.write(reinterpret_cast<char*>(&data), sizeof(DataType));
    file_.flush();
}

void File::write(DataType* data, size_t count)
{
    file_.write(reinterpret_cast<char*>(data), sizeof(DataType) * count);
    file_.flush();
}

bool File::read(DataType& data)
{
    if (file_.read(reinterpret_cast<char*>(&data), sizeof(DataType))) {
        return true;
    }
    return false;
}

bool File::read(size_t pos, DataType& data)
{
    seek(pos);
    return read(data);
}

bool File::read(size_t pos, DataType* buf, size_t elems)
{
    seek(pos);
    if (file_.read(reinterpret_cast<char*>(buf), sizeof(DataType) * elems)) {
        return true;
    }
    return false;
}

bool File::readRevers(DataType& data)
{
    if (reverseStatus_ == STOP) {
        file_.seekg(sizeof(DataType) * -1, std::ios::end);
        reverseStatus_ = PROCESS;
    }
    else {
        file_.seekg(sizeof(DataType) * -2, std::ios::cur);
        if (!file_) {
            reverseStatus_ = STOP;
            file_.clear();
            file_.seekg(0, std::ios::beg);
            return false;
        }
    }
    if (!read(data)) {
        reverseStatus_ = STOP;
        return false;
    }

    return true;
}

void File::seek(size_t pos)
{
    file_.clear();

    std::streampos nextPos = pos * sizeof(DataType);
    file_.seekp(0, std::ios::beg);
    file_.seekg(0, std::ios::beg);
    file_.seekp(nextPos);
    file_.seekg(nextPos);
    checkStatus();
}

size_t File::size() const
{
    file_.seekg(0, std::ios::end);
    size_t size = file_.tellg();
    file_.seekg(0, std::ios::beg);

    return size / sizeof(DataType);
}

bool File::empty() const
{
    return size() == 0;
}

void File::print()
{
    seek(0);
    DataType data;
    std::cerr << "data: " << std::endl;
    while (read(data)) {
        std::cerr << data << " ";
    }
    std::cerr << std::endl;
}

void File::checkStatus()
{
    if (!file_) {
        perror("Error while opening file");
        exit(1);
    }
}

RandomGenerator::RandomGenerator(const std::string& path, size_t size)
    : File(path)
    , size_(size)
{
    if (empty()) {
        generate();
    }
}

static void fillRandomBuf(DataType* buf, size_t size, std::mt19937& g, std::uniform_int_distribution<DataType>& uni)
{
    for (int i = 0; i < size; ++i) {
        buf[i] = uni(g);
    }
}

void RandomGenerator::generate()
{
    const int bufSize = 1000;
    DataType buf[bufSize];
    std::random_device rd;
    std::mt19937 g(rd());
    std::uniform_int_distribution<DataType> uni(0, std::numeric_limits<DataType>::max());

    std::int64_t sizeLeft = size_;
    size_t curSize = 0;
    while (sizeLeft > 0) {
        curSize = sizeLeft - 1000 > 0 ? 1000 : sizeLeft;
        fillRandomBuf(buf, curSize, g, uni);
        write(buf, curSize);
        sizeLeft -= curSize;
    }
}

ZeroGenerator::ZeroGenerator(const std::string& path, size_t size)
    : File(path)
    , size_(size)
{
    if (empty()) {
        generate();
    }
}

void ZeroGenerator::generate()
{
    DataType empty[1000];
    std::memset(empty, 0, sizeof(DataType) * 1000);
    std::int64_t sizeLeft = size_;
    size_t curSize = 0;
    while (sizeLeft > 0) {
        curSize = sizeLeft - 1000 > 0 ? 1000 : sizeLeft;
        write(empty, curSize);
        sizeLeft -= curSize;
    }
}

} // namespace bin_file
