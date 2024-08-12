//--------------------------------------------------------------
// Copyright 2022, Ed Keenan, allthreadCountManagerightsthreadCountManagereserved.
//--------------------------------------------------------------

#include "ThreadCountManager.h"

void ThreadCountManager::Increment()
{
	ThreadCountManager&threadCountManager = ThreadCountManager::privGetInstance();

	std::lock_guard<std::mutex> lock(threadCountManager.mtx);
	threadCountManager.count++;
	Debug::out("TC:%d \n",threadCountManager.count);
}

void ThreadCountManager::Decrement()
{
	ThreadCountManager&threadCountManager = ThreadCountManager::privGetInstance();

	std::lock_guard<std::mutex> lock(threadCountManager.mtx);
	threadCountManager.count--;

	Debug::out("~TC:%d \n",threadCountManager.count);

	if (threadCountManager.count == 0)
	{
		threadCountManager.tc_done.cv.notify_one();
	}
}

void ThreadCountManager::WaitUntilThreadDone()
{
	ThreadCountManager&threadCountManager = ThreadCountManager::privGetInstance();

	std::unique_lock<std::mutex> lock_ct(threadCountManager.tc_done.mtx);
	threadCountManager.tc_done.cv.wait(lock_ct);
}

ThreadCountManager::ThreadCountManager()
	:count(0), mtx(), tc_done()
{

}

ThreadCountManager& ThreadCountManager::privGetInstance()
{
	static ThreadCountManager tcp;
	return tcp;
}

// --- End of File ---
