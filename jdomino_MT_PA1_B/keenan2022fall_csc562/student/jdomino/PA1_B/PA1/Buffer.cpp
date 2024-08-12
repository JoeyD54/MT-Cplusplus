//--------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//--------------------------------------------------------------

#include "Buffer.h"

Buffer::Buffer(size_t s)
	: status(BufferStatus::EMTPY),
	poBuff(new unsigned char[s]()),
	mtx(),
	totalSize(s),
	currSize(0),
	usedSize(0)	
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
const size_t Buffer::GetUsedSize() const
{
	return this->usedSize;
}

void Buffer::SetCurrSize(const size_t s)
{
	assert(s <= this->totalSize);
	this->currSize = s;
}
void Buffer::SetUsedSize(const size_t s)
{
	this->usedSize = s;
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

// --- End of File ---