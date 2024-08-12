
#ifndef COORD_THREAD_H
#define COORD_THREAD_H

#include "ThreadBase.h"
#include "FileCoordShare.h"
#include "Buffer.h"
#include "CircularData.h"
#include "WaveBuffThread.h"

struct KillShare;

class CoordinatorThread : public ThreadBase
{
public:
	static const unsigned int BUFFER_SIZE = 512 * 1024;

	enum class Status
	{
		CoordThreadBuffer_Ready,
		CoordThreadBuffer_Not_Ready
	};

public:
	CoordinatorThread(const char* const pName, KillShare& _kill_var, FileCoordShare& share_fc, CircularData& _inQueue);
	CoordinatorThread() = delete;
	CoordinatorThread(const CoordinatorThread&) = delete;
	CoordinatorThread& operator = (const CoordinatorThread&) = delete;
	~CoordinatorThread();

	void operator()() override;
	static unsigned char* GetNext2KBuff();

private:

	static CoordinatorThread& privGetInstance();
	static CoordinatorThread* pInstance;

	// --------------------------
	// Data
	// --------------------------

	FileCoordShare& share_fc;

	Buffer* pBuff_A;
	Buffer* pBuff_B;

	Buffer* pFillBuffer;
	Buffer* pDrainBuffer;

	//A when true, B when false
	bool currentBuffFlag;

	CircularData& inQueue;
	Status status;

	unsigned char* bufferTag;
};

#endif

// --- End of File ---
