#ifndef COORDINATOR_THREAD_H
#define COORDINATOR_THREAD_H

#include "ThreadCount.h"
#include "FileCoorShare.h"
#include "Buffer.h"
#include "CircularData.h"
#include "Command.h"
#include "FileThread.h"

class CoordinatorThread : public BannerBase
{
public:
	static const unsigned int BUFFER_SIZE = 512 * 1024;

public:
	CoordinatorThread() = delete;
	CoordinatorThread(const CoordinatorThread&) = default;
	CoordinatorThread(const char* const pName, std::future<void>&_tFuture, FileCoorShare& _inFCS, CircularData& _inCircleBuffer);
	CoordinatorThread& operator = (const CoordinatorThread&) = default;
	~CoordinatorThread();


	void operator()();
	void Launch();

private:
	//Data:--------
	FileCoorShare& share_fc;
	CircularData& inCircleData;

	Buffer* pBuff_A;
	Buffer* pBuff_B;

	Buffer* pFillBuffer;
	Buffer* pDrainBuffer;

	std::thread mThread;
	std::future<void>& tFuture;

};

#endif

