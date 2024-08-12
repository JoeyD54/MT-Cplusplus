#include "Buffer.h"

Buffer::Buffer(size_t s)
    : poBuff(new unsigned char[s]()),
    mtx(),
    totalSize(s),
    currSize(0)
{
    assert(poBuff);
}

unsigned char* Buffer::GetRawBuff()
{
    assert(poBuff);
    return this->poBuff;
}

const size_t Buffer::GetTotalSize() const
{
    return this->totalSize;
}

const size_t Buffer::GetCurrSize() const
{
    return this->currSize;
}

void Buffer::SetCurrSize(const size_t s)
{
    assert(s <= this->totalSize);
    this->currSize = s;
}

std::mutex& Buffer::GetMutex()
{
    return this->mtx;
}

Buffer::~Buffer()
{
    delete poBuff;
    poBuff = nullptr;
}