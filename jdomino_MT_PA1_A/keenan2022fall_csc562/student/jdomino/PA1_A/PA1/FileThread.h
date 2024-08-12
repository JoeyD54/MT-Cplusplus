#ifndef FILE_THREAD_H
#define FILE_THREAD_H

#include "ThreadCount.h"
#include "FileSlow.h"
#include "Buffer.h"
#include "FileCoorShare.h"

class FileThread : public BannerBase
{
public:
	static const unsigned int BUFFER_SIZE = 512 * 1024;
	static const unsigned int FILE_NAME_SIZE = 12;
	static const int MAX_NUM_FILES = 23;

	enum class Status
	{
		EMPTY,
		READY
	};

	FileThread() = delete;
	FileThread(const FileThread&) = default;
	FileThread(const char* const pName, std::future<void>& _tFuture, FileCoorShare& _share_fc);
	FileThread& operator = (const FileThread&) = default;
	~FileThread();

	static size_t CopyBuffer(Buffer* pDest);

	void operator()();
	void Launch();

private:
	char* privGetFileName(int index);
	void privLoadFile(const char* const pFileName);

	static FileThread* pInstance;
	static FileThread& privGetInstance();

	//Data:--------
	std::thread mThread;
	std::future<void>& tFuture;

	FileCoorShare& share_fc;

	int numFilesRead;	 
	char* poFileName;
	Buffer *poBuff;
	Status status;
	FileSlow::Handle fh;
	DWORD currBuffSize = 0;
	unsigned char* pBottomBuffer;
};

#endif
