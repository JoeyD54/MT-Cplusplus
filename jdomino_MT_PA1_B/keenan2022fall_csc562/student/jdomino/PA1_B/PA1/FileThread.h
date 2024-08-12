//--------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//--------------------------------------------------------------

#ifndef FILE_THREAD_H
#define FILE_THREAD_H

#include "ThreadBase.h"
#include "FileCoordShare.h"
#include "Buffer.h"

struct KillShare;

class FileThread : public ThreadBase
{
public:
	static const unsigned int BUFFER_SIZE = 512 * 1024;
	static const unsigned int FILE_NAME_SIZE = 12;
	static const int MAX_NUM_WAVE_FILES = 23;

public:
	FileThread(const char* const pName,
		KillShare& _kill_var,
		FileCoordShare& share_fc);

	FileThread() = delete;
	FileThread(const FileThread&) = delete;
	FileThread& operator = (const FileThread&) = delete;
	~FileThread();

	void operator()() override;	
	static size_t CopyBuffer(Buffer* pDest);	

private:
	char* privGetFileName(int index);
	void privLoadFile(const char* const pFileName);

	static FileThread *pInstance;
	static FileThread& privGetInstance();

	// --------------------------
	// Data
	// --------------------------

	Buffer *poBuff;
	char* poFileName;
	int numFilesRead;
	FileCoordShare& share_fc;
};

#endif

// --- End of File ---
