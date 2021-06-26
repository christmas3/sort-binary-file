#pragma once

#include <cstdint>
#include <fstream>
#include <string>

namespace bin_file {
using DataType = std::uint16_t;

struct IFile
{
    virtual const std::string& path() const = 0;

    virtual void write(DataType) = 0;
    virtual void write(DataType*, size_t count) = 0;
    virtual bool read(DataType&) = 0;
    virtual bool read(size_t, DataType&) = 0;
    virtual bool read(size_t pos, DataType* buf, size_t elems) = 0;
    virtual bool readRevers(DataType&) = 0;
    virtual void seek(size_t) = 0;

    virtual size_t size() const = 0;
    virtual bool empty() const = 0;
    virtual void print() = 0;

    virtual ~IFile() {}
};

class File : public IFile
{
public:
    explicit File(const std::string& path);

    const std::string& path() const override { return path_; }

    void write(DataType) override;
    void write(DataType* type, size_t count) override;
    bool read(DataType&) override;
    bool read(size_t, DataType&) override;
    bool read(size_t pos, DataType* buf, size_t elems) override;
    bool readRevers(DataType& type) override;
    void seek(size_t) override;
    size_t size() const override;
    bool empty() const override;
    void print() override;

private:
    void checkStatus();

    mutable std::fstream file_;
    const std::string path_;

    enum ReverseReadStatus
    {
        STOP,
        PROCESS
    };
    ReverseReadStatus reverseStatus_;
};

class RandomGenerator : public File
{
public:
    explicit RandomGenerator(const std::string& path, size_t size);

private:
    void generate();
    size_t size_;
};

class ZeroGenerator : public File
{
public:
    explicit ZeroGenerator(const std::string& path, size_t size);

private:
    void generate();
    size_t size_;
};

} // namespace bin_file
