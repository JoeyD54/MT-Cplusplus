#ifndef BUFFER_H
#define BUFFER_H

struct Buffer
{
public:
    Buffer(size_t size);

    Buffer() = delete;
    Buffer(const Buffer&) = delete;
    Buffer& operator = (const Buffer&) = delete;
    ~Buffer();

    unsigned char* GetRawBuff();
    const size_t GetTotalSize() const;
    const size_t GetCurrSize() const;
    void   SetCurrSize(const size_t s);
    std::mutex& GetMutex();

private:
    unsigned char* poBuff;
    std::mutex     mtx;

    size_t         totalSize;
    size_t         currSize;
};

#endif