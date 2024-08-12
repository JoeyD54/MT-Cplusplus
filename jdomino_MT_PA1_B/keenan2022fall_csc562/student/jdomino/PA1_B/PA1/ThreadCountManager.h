//--------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//--------------------------------------------------------------

#ifndef THREAD_COUNT_PROXY
#define THREAD_COUNT_PROXY

class ThreadCountManager
{
public:
	struct ThreadCountDone
	{
		std::mutex				 mtx;
		std::condition_variable  cv;
	};

public:
	static void Increment();
	static void Decrement();
	static void WaitUntilThreadDone();

private:
	ThreadCountManager();
	static ThreadCountManager& privGetInstance();

private:
	// Data
	int        count;
	std::mutex mtx;

	ThreadCountDone tc_done;
};

#endif

// --- End of File ---

