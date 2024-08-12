//--------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//--------------------------------------------------------------

#ifndef BUFFER_H
#define BUFFER_H

enum BufferStatus
{
	EMTPY,
	FULL
};

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
	const size_t GetUsedSize() const;
	void   SetCurrSize(const size_t s);
	void   SetUsedSize(const size_t s);
	std::mutex& GetMutex();

	BufferStatus status;

private:
	unsigned char* poBuff;
	std::mutex     mtx;

	size_t         totalSize;
	size_t         currSize;
	size_t         usedSize;
};



#endif

// --- End of File ---

